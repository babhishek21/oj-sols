#include<bits/stdc++.h>

using namespace std;

int max(int a, int b) {
	return (a>b) ? a : b;
}

void lcs(const char *X, const char *Y, int n, int m) {
	int L[n+1][m+1] = {0};

	/* bottom up DP approach */
	for(int j=0; j<=m; j++)
	  L[n][j] = 0;
	
	for (int i = n-1; i >= 0; i--) {
	  L[i][m] = 0;
	  
		for (int j = m-1; j >= 0; j--) {
		  
		  if(X[i] == Y[j]) {
				L[i][j] = 1 + L[i+1][j+1];
			} else {
				L[i][j] = max(L[i+1][j], L[i][j+1]);
			}

		}
	}

	/* crazy verbose print */
	int index = L[0][0];

	if(index <= 1) {
		printf("N\n");
		return;
	}

	printf("Y\n%d\n", index);

	int i=0, j=0;
	while(i<n && j<m) {
		if(X[i] == Y[j]) {
			printf("%c %d %d\n", X[i], i+1, j+1);
			i++; j++;
		} else {
			(L[i+1][j] > L[i][j+1]) ? i++ : j++;
		}
	}


}

int main() {
	int t;
	char x[1001], y[1001];
	int n, m;

	scanf("%d", &t);

	for (int i = 0; i < t; ++i) {
		scanf("%d %s", &n, x);
		scanf("%d %s", &m, y);

		printf("case %d ", i+1);

		lcs(x, y, n, m);
	}

	return 0;
}
