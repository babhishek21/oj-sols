#include<bits/stdc++.h>
using namespace std;

int main() {
	int s[100], n;
	vector <int> lhs, rhs;
	long long ans = 0;
	
	scanf("%d", &n);
	
	for(int i=0; i<n; i++) {
		scanf("%d", &s[i]);
	}

	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			for(int k=0; k<n; k++) {
				lhs.push_back(s[i]*s[j]+s[k]);
				
				if(s[i] != 0)
					rhs.push_back(s[i]*(s[j]+s[k]));
			}
	
	sort(lhs.begin(), lhs.end());
	sort(rhs.begin(), rhs.end());
	
	for(auto it = lhs.begin(); it != lhs.end(); ++it) {
		auto bounds = equal_range(rhs.begin(), rhs.end(), *it);
		ans += bounds.second - bounds.first;
	}
	
	printf("%lld", ans);
}