#include<bits/stdc++.h>
using namespace std;

int n, a, b;
int arr[34];

int main() {
	vector<long long> lhs, rhs;
	long long sum;

	scanf("%d %d %d", &n, &a, &b);

	for (int i=0; i<n; i++)
		scanf("%d", &arr[i]);

	int h1 = (n+1)/2, h2 = n - h1;

	for (int i = 0; i < (1<<h1); ++i) {
		sum = 0;
		for (int j = 0; j < h1; ++j) {
			if((i & 1<<j) != 0)
				sum += arr[j];
		}

		lhs.push_back(sum);
	}

	for (int i = 0; i < (1<<h2); ++i) {
		sum = 0;
		for (int j = 0; j < h2; ++j) {
			if((i & 1<<j) != 0)
				sum += arr[h1+j];
		}

		rhs.push_back(sum);
	}

	sort(lhs.begin(), lhs.end());
	sort(rhs.begin(), rhs.end());

	sum = 0;

	for (auto it = lhs.begin(); it != lhs.end(); ++it) {
		auto lo = lower_bound(rhs.begin(), rhs.end(), a - *(it));
		auto hi = upper_bound(rhs.begin(), rhs.end(), b - *(it));
		sum += hi - lo;
	}

	printf("%lld\n", sum);
}