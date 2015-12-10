#include <bits/stdc++.h>
using namespace std;

vector <int> pos;

bool fit (int x, int c, int n) {
	int temp = 1, last_pos = pos[0];
	for (int i=1; i<n; i++) {
		if ((pos[i] - last_pos) >= x){
			temp++;
			last_pos = pos[i];
		}

		if(temp == c)
			return true;
	}

	return false;
}

int main() {
	int t;

	scanf("%d", &t);

	while (t--) {
		int n, c, temp;

		scanf("%d %d", &n, &c);

		for (int i=0; i<n; i++) {
			scanf("%d", &temp);
			pos.push_back(temp);
		}

		sort(pos.begin(), pos.end());

		int lo = pos.back();
		for(int i=1; i<n; ++i) {
			lo = (temp = pos[i]-pos[i-1]) < lo ? temp : lo;
		}

		int hi = pos.back() - pos.front();
		int mid;

		// printf("%d %d\n", lo, hi);		//DEBUG

		while (lo < hi) {
			mid = lo + (hi-lo+1)/2;

			if(fit(mid, c, n))
				lo = mid;
			else
				hi = mid-1;

			// printf("%d %d %d\n", lo, mid, hi);	//DEBUG
		}

		// if (!fit(hi)) => complain

		// return hi
		printf("%d\n", hi);

		pos.clear();
	}

	return 0;
}