#include<bits/stdc++.h>
using namespace std;

int main() {
	int a[4000];
	int b[4000];
	int c[4000];
	int d[4000];
	vector <int> lhs, rhs;
	int ans = 0;
	int n;
	
	scanf("%d", &n);
	
	for(int i=0; i<n; i++) {
		scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
	}

	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++) {
			lhs.push_back(a[i]+b[j]);
			rhs.push_back(c[i]+d[j]);
		}
		
	sort(lhs.begin(), lhs.end());
	sort(rhs.begin(), rhs.end());
	
	for(auto it = lhs.begin(); it != lhs.end(); ++it) {
		auto bounds = equal_range(rhs.begin(), rhs.end(), -(*it));
		ans += bounds.second - bounds.first;
	}
	
	printf("%d", ans);
}