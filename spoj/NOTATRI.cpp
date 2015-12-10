#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	int a[2000];

	scanf("%d", &n);

	while(n != 0) {
		int lo, hi, mid;

		for (int i=0; i<n; i++) {
			scanf("%d", &a[i]);
		}

		sort(a, a+n);

		int counter = 0;
		for (int i = 0; i < n-2; ++i)
			for (int j = i+1; j < n-1; ++j) {
				lo = j+1;
				hi = n-1;
				
				while (lo < hi) {
					mid = lo + (hi-lo)/2;

					if(a[mid] > a[i] + a[j])
						hi = mid;
					else
						lo = mid+1;
				}
				
				if(a[lo] <= a[i] + a[j])
					continue;
				
				counter += n-lo;
			}

		printf("%d\n", counter);

		scanf("%d", &n);
	}

	return 0;
}