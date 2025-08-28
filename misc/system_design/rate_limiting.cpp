/**
 * Problem: Rate Limiting Strategies
 *
 * Further reading:
 * 		https://stripe.com/blog/rate-limiters
 * 		https://blog.cloudflare.com/counting-things-a-lot-of-different-things/
 * 		https://tech.groww.in/rate-limiter-and-its-algorithms-with-illustrations-564455162935
 * 		https://medium.com/figma-design/an-alternative-approach-to-rate-limiting-f8a06cf7c94c
 * 		https://engineering.classdojo.com/blog/2015/02/06/rolling-rate-limiter/
 *
 * WARN: The current implementations have bugs where refills/leaks are not pro-rated to CPU ticks. Instead they
 * 	fill up at a resolution of 1 sec or more. So, at a fill rate of 2 units / sec, will only fill up 2 units after 1s,
 * 	but won't fill up anything after 500ms. This is obviously not ideal for real-world implementation.
 * 	More reading: https://philippegroarke.com/posts/2018/chrono_for_humans/
 * 	More reading: https://www.reddit.com/r/cpp/comments/a2jcks/comment/eazsoqx/
 *
 * Author: babhishek21
 * Lang: C++11
 */

#include <bits/stdc++.h>
#include "custom/prettyprint.hpp" // C++11 only
using namespace std;

#define debug(x) cerr << #x << " : " << x << endl;

/**
 * Token Bucket - Allows bursts of traffic. No fixed rate of processing.
 *
 * refill() and consume() operations might not be atomic, so the limiter can be too lenient in a distributed environment.
 * Can use Redis Hash and Lua scripts (which are run atomically in Redis) for this.
 */
class TokenBucket {

	unsigned int capacity,
	refill_rate,	// in units / second
	tokens;

	chrono::time_point<chrono::system_clock> last_refill_timestamp;

	void refill() {
		const auto now = chrono::system_clock::now();
		const auto seconds_elapsed = chrono::duration_cast<chrono::seconds>(now - last_refill_timestamp).count();
		const auto tokens_to_add = seconds_elapsed * refill_rate;

		tokens = min(capacity, tokens + (unsigned int)tokens_to_add);
		last_refill_timestamp = now;
	}

public:
	TokenBucket(unsigned int capacity, unsigned int refill_rate):
		capacity(capacity),
		refill_rate(refill_rate),
		tokens(capacity),
		last_refill_timestamp(chrono::system_clock::now()) {};

	bool consume(unsigned int need = 1) {
		refill();

		if (tokens >= need) {
			tokens -= need;
			return true;
		}

		return false;
	}
};

/**
 * Leaky Bucket - Smooths out bursts. Constant outflow/processing rate; burst requests can overflow and get rejected.
 *
 * Can use Redis Lists as a FIFO queue in place of thread-safe queues, for distributed systems.
 */
class LeakyBucket {
	unsigned int capacity,
	leak_rate;		// in units / sec

	deque<string> requests; // request_ids are stored here

	chrono::time_point<chrono::system_clock> last_leak_timestamp;

	void leak() {
		const auto now = chrono::system_clock::now();
		const auto seconds_elapsed = chrono::duration_cast<chrono::seconds>(now - last_leak_timestamp).count();
		const auto request_count_to_leak = min(capacity, (unsigned int)seconds_elapsed * leak_rate);

		// debug(request_count_to_leak)

		// if(request_count_to_leak > 0)
		// 	debug(vector<string>(requests.begin(), requests.begin() + min((deque<string>::size_type)request_count_to_leak, requests.size())));

		/* De-queue leaked amount of requests. It is assumed that a separate consumer
			worker has already started processing these requests. */
		requests.erase(requests.begin(),
			requests.begin() + min((deque<string>::size_type)request_count_to_leak, requests.size()));

		last_leak_timestamp = now;
	}

public:
	LeakyBucket(unsigned int capacity, unsigned int leak_rate):
		capacity(capacity),
		leak_rate(leak_rate),
		last_leak_timestamp(chrono::system_clock::now()) {};

	bool enqueue(const string& request_id) {
		leak();

		if(requests.size() < capacity) {
			requests.push_back(request_id);	// enqueue request
			return true;
		}

		return false;
	}
};

/**
 * Fixed Window Counter - Simplest, but can lead to bursts at window boundaries (allowing upto 2x the limit).
 *
 * Can use simple (key: window, value: count of requests) pair in Redis and auto expire key after window duration.
 */
class FixedWindowCounter {
	unsigned int capacity,
	window_size;	// in seconds

	unsigned int request_count;
	chrono::time_point<chrono::system_clock> window_start_timestamp;

	void reset_window() {
		window_start_timestamp = chrono::system_clock::now();
		request_count = 0;
	}

public:
	/**
	 * In this implementation, each user would get their own FixedWindowCounter instance.
	 */
	FixedWindowCounter(unsigned int capacity, unsigned int window_size):
		capacity(capacity),
		window_size(window_size),
		request_count(0),
		window_start_timestamp(chrono::system_clock::now()) {};

	bool allow_request() {
		const auto now = chrono::system_clock::now();
		const auto seconds_elapsed = chrono::duration_cast<chrono::seconds>(now - window_start_timestamp).count();

		if(seconds_elapsed >= window_size)
			reset_window();

		if(request_count < capacity) {
			request_count++;
			return true;
		}

		return false;
	}
};

/**
 * Sliding window log - Most accurate, but requires storing of timestamps of all requests.
 *
 * Can use Redis Sorted Sets (with timestamp as score) to store request timestamps.
 * Note: Using Redis MULTI atomic trnsactions can be memory heavy since logs are recorded even when requests are denied.
 * 		MULTI
 * 		ZREMRANGEBYSCORE(KEY, 0, NOW() - WINDOW)
 * 		ZADD(KEY, NOW(), UUID)						<-- If this isn't added now, another network call would be needed to conditionally add accepted requests. That can cause race conditions.
 *		ZRANGEWITHSCORES(KEY, 0, -1)			<-- could be ZCARD as well, if you don't care about the timestamps
 * 		EXPIRE(KEY, WINDOW + 1)						<-- +1 to account for any network latency
 * 		EXEC
 *
 * The implementation here only adds the request timestamp if the request is accepted. We can use Lua scripts
 * (which are run atomically in Redis) to emulate this in Redis.
 */
class SlidingWindowLog {
	unsigned int capacity,
		window_size;	// in seconds

	deque<chrono::time_point<chrono::system_clock>> request_timestamps;

	void evict_old_requests() {
		const auto time_point_threshold = chrono::system_clock::now() - chrono::seconds(window_size);

		request_timestamps.erase(request_timestamps.begin(),
			upper_bound(request_timestamps.begin(), request_timestamps.end(), time_point_threshold));
	}

public:
	SlidingWindowLog(unsigned int capacity, unsigned int window_size):
		capacity(capacity),
		window_size(window_size) {};

	bool allow_request() {
		evict_old_requests();

		if(request_timestamps.size() < capacity) {
			request_timestamps.push_back(chrono::system_clock::now());
			return true;
		}

		return false;
	}
};

/**
 * Sliding window counter - Hybrid of fixed window counter and sliding window log. Fixes edge-burst and memory efficiency problems.
 * Sacrifices accuracy for effectiveness by smooth-approximating the inflow rate of requests based on how the window moves.
 *
 * Can use Redis Hash and Lua scripts (which are run atomically in Redis) for this.
 *
 * Note: This implementation is Cloudflare style: https://blog.cloudflare.com/counting-things-a-lot-of-different-things/
 * Another style (Figma): https://medium.com/figma-design/an-alternative-approach-to-rate-limiting-f8a06cf7c94
 * Both have their pros and cons. The Cloudflare one is easier to implement, but can be slightly more lenient.
 * The Figma one is more accurate, but requires more bookkeeping (storing counts for multiple sub-windows).
 */
class SlidingWindowCounter {
	unsigned int capacity,
		window_size, 					// in seconds
		previous_window_count,
		current_window_count;

	chrono::time_point<chrono::system_clock> current_window_start; // time point
	chrono::seconds window_duration;		// window_size as duration

	float reset_window_if_needed(chrono::time_point<chrono::system_clock> now) {
		const auto time_elapsed = now - current_window_start;
		const auto delta_into_current_window = time_elapsed % window_duration;
		const auto ratio = delta_into_current_window / chrono::duration_cast<chrono::duration<float>>(window_duration);

		if(time_elapsed >= window_duration) {
			previous_window_count = time_elapsed >= 2 * window_duration ? 0 : current_window_count;
			current_window_count = 0;
			current_window_start = now - delta_into_current_window;
		}

		// debug(time_elapsed.count());
		// debug(delta_into_current_window.count());
		// debug(ratio);

		return ratio;
	}

public:
	SlidingWindowCounter(unsigned int capacity, unsigned int window_size):
		capacity(capacity),
		window_size(window_size),
		previous_window_count(0),
		current_window_count(0),
		current_window_start(chrono::system_clock::now()) {
			window_duration = chrono::seconds(window_size);
		};

	bool allow_request() {
		const auto now = chrono::system_clock::now();
		const auto delta_into_current_window_ratio = reset_window_if_needed(now);

		const unsigned int effective_count = floor(previous_window_count * (1 - delta_into_current_window_ratio)) + current_window_count;

		// debug(previous_window_count);
		// debug(current_window_count);
		// debug(delta_into_current_window_ratio);
		// debug(effective_count);
		// debug("-------");

		if(effective_count < capacity) {
			current_window_count++;
			return true;
		}

		return false;
	}
};

/* Tests */

void test_TokenBucket() {

	TokenBucket limiter(2, 1);	// 2 requests every second

	vector<bool> results;

	results.push_back(limiter.consume());
	results.push_back(limiter.consume());
	results.push_back(limiter.consume());

	this_thread::sleep_for(1s);

	results.push_back(limiter.consume());
	results.push_back(limiter.consume());
	results.push_back(limiter.consume());

	assert(results == vector<bool>({true, true, false, true, false, false}));
}

void test_LeakyBucket() {
	LeakyBucket limiter(2, 1);	// 2 requests every second

	vector<bool> results;

	results.push_back(limiter.enqueue("abc"));
	results.push_back(limiter.enqueue("def"));
	results.push_back(limiter.enqueue("ijk"));

	this_thread::sleep_for(1s);

	results.push_back(limiter.enqueue("xyz"));
	results.push_back(limiter.enqueue("pqr"));
	results.push_back(limiter.enqueue("lmn"));

	assert(results == vector<bool>({true, true, false, true, false, false}));
}

void test_FixedWindowCounter1() {
	FixedWindowCounter limiter(2, 2); // 2 requests every 2 seconds

	vector<bool> results;

	results.push_back(limiter.allow_request());
	results.push_back(limiter.allow_request());
	results.push_back(limiter.allow_request());

	this_thread::sleep_for(2s);

	results.push_back(limiter.allow_request());
	results.push_back(limiter.allow_request());
	results.push_back(limiter.allow_request());

	assert(results == vector<bool>({true, true, false, true, true, false}));
}

void test_FixedWindowCounter2() {
	// Test edge bursts
	FixedWindowCounter limiter(2, 1); // 2 requests every second

	vector<bool> results;

	results.push_back(limiter.allow_request());
	this_thread::sleep_for(800ms);
	results.push_back(limiter.allow_request()); // edge request
	this_thread::sleep_for(200ms);
	results.push_back(limiter.allow_request()); // edge request
	results.push_back(limiter.allow_request()); // edge request
	results.push_back(limiter.allow_request());
	results.push_back(limiter.allow_request());

	// debug(results);

	assert(results == vector<bool>({true, true, true, true, false, false}));
}

void test_SlidingWindowLog() {
	SlidingWindowLog limiter(2, 2); // 2 requests every 2 seconds

	vector<bool> results;

	results.push_back(limiter.allow_request());
	results.push_back(limiter.allow_request());
	results.push_back(limiter.allow_request());

	this_thread::sleep_for(2s);

	results.push_back(limiter.allow_request());
	results.push_back(limiter.allow_request());
	results.push_back(limiter.allow_request());

	assert(results == vector<bool>({true, true, false, true, true, false}));
}

void test_SlidingWindowCounter() {
	SlidingWindowCounter limiter(3, 1);  // 3 requests every second

	vector<bool> results;

	results.push_back(limiter.allow_request());
	results.push_back(limiter.allow_request());
	results.push_back(limiter.allow_request());
	results.push_back(limiter.allow_request());

	this_thread::sleep_for(1550ms);		// enough time for window to slide and ~2 requests to expire

	results.push_back(limiter.allow_request());
	results.push_back(limiter.allow_request());
	results.push_back(limiter.allow_request());

	// debug(results);

	assert(results == vector<bool>({true, true, true, false, true, true, false}));
}

int main() {

  vector<thread> tests;
  tests.emplace_back(test_TokenBucket);
  tests.emplace_back(test_LeakyBucket);
  tests.emplace_back(test_FixedWindowCounter1);
  tests.emplace_back(test_FixedWindowCounter2);
  tests.emplace_back(test_SlidingWindowLog);
  tests.emplace_back(test_SlidingWindowCounter);

  for(auto& test: tests)
  	test.join();

  cout << "all tests passed!" << endl;

  return 0;
}