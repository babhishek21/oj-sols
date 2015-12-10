#include <bits/stdc++.h>
using namespace std;

int N;
int tr[2000];
int cache[2000][2000];

int opti(int beg, int fin) {
	if(beg > fin)	return 0;
	
	if(cache[beg][fin] != 0)	return cache[beg][fin];
	
	int time = N - (fin - beg + 1) + 1;
	return cache[beg][fin] = max(
		opti(beg+1, fin) + time*tr[beg],
		opti(beg, fin-1) + time*tr[fin] );
}

int main() {
	scanf("%d", &N);
	
	for(int i=0; i<N; i++)
		scanf("%d", &tr[i]);
	
	printf("%d", opti(0, N-1));
	
	return 0;
}