/**
 * Custom Binary Search template over continuous value ranges
 * i.e. for cases when you need to search over the continuous value range [lo, hi] (instead of discrete values in a container)
 */

#include <iostream>
using namespace std;

// Finds the smallest x in [lo, hi] such that pred(x) is true.
// PRECONDITION: pred is monotonic over [lo, hi]: false...false, true...true
// PRECONDITION: pred(hi) must be true (otherwise no answer exists in range)
// Returns hi+1-equivalent behavior is NOT handled -> caller must ensure pred(hi) is true,
// or check the return value's predicate afterward if existence isn't guaranteed.
template<typename T, typename Pred>
T firstTrue(T lo, T hi, Pred pred) {
  while(lo < hi) {
    T mid = lo + (hi-lo)/2;

    if(pred(mid))
      hi = mid;
    else
      lo = mid + 1;
  }

  return lo;
}

// In case of the mirror case: pred is monotic over [lo, hi]: true...true, false...false
// Finds the largest x in [lo, hi] such that pred(x) is true.
// PRECONDITION: pred(lo) must be true.
template <typename T, typename Pred>
T lastTrue(T lo, T hi, Pred pred) {
  while (lo < hi) {
    T mid = lo + (hi - lo + 1) / 2;   // ceil, to avoid infinite loop when hi = mid
    
    if (pred(mid))
      lo = mid;
    else
      hi = mid - 1;
  }

  return lo;   // == hi, last x where pred(x) is true
}

// You can also find lastTrue by simply calculating firstTrue on the inverse predicate
// (i.e. !pred()) and then subtract 1
// GOTCHA: If pred() is true for the entire range, then !pred() is false everywhere. We
// can instead search in the range [lo, hi+1), with hi+1 returned when not found.
template <typename T, typename Pred>
T lastTrueAlt(T lo, T hi, Pred pred) {
  hi = hi + 1;                      // sentinel: firstTrue(!pred) always has an answer now

  while (lo < hi) {
    T mid = lo + (hi - lo) / 2;

    if (!pred(mid))
      hi = mid;
    else
      lo = mid + 1;
  }

  return lo - 1;
}

/* Sample implementations */

// Over value domain [lo, hi], find first x with x >= k
template <typename T>
T LowerBound(T lo, T hi, T k) {
  return firstTrue(lo, hi, [k](T x) { return x >= k; });
}

// Over value domain [lo, hi], find first x with x > k
template <typename T>
T UpperBound(T lo, T hi, T k) {
    return firstTrue(lo, hi, [k](T x) { return x > k; });
}

int main() {

  auto chk = [&](const string& name, long long got, long long exp) {
    cerr << (got == exp ? "\033[32mPASS\033[0m" : "\033[31mFAIL\033[0m")
         << " " << name << ": got=" << got << " exp=" << exp << "\n";
  };

  chk("", firstTrue(-100, 100, [](int x) { return x > -x; }), 1);
  chk("", lastTrue(-100, 100, [](int x) { return x < -x; }), -1);

  return 0;
}
