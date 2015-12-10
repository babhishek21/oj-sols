#include <bits/stdc++.h>
using namespace std;

void op (vector<int>& v) {
	for (int i = 0; i < v.size(); ++i) {
		printf("%d ", v[i]);
	}
	printf("\n");

	return;
}

int main() {
	int n;
	long long x;
	vector<int> lhs, rhs;

	scanf("%d %lld", &n, &x);
	
	/*
		This is classic example of bianry search using bits-sets.
		Let X be difference b/w left scale and right scale.
		Our aim is to reduce X to 0 using the N powers of 3 given
		to us. Algo:
		
		for each power of 3 from 3^0 to 3^N:
			1.	if X%3==2, we add 1 to left scale, to make X a power of 3.
			2.	if X%3==1, we add 1 to right scale to reduce X to power of 3.
			3.	X = X/3 (to provide power of 3 scaling when 1 is used in above
				two steps.)
		if X!=0:
			reduction not possible with given N
		else:
			output
	*/

	for (int i = 0; i < n; ++i) {
		if(x%3 == 2) {
			lhs.push_back(i+1);
			x++;
		} else if(x%3 == 1) {
			rhs.push_back(i+1);
			x--;
		}

		x/=3;
	}

	if(x != 0)
		printf("-1\n");
	else {
		op(lhs);
		op(rhs);
	}

	return 0;
}