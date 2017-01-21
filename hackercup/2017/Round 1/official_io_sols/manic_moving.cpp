// Hacker Cup 2017
// Round 1
// Manic Moving
// Jacob Plachta

#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <sstream>
using namespace std;

#define LL long long
#define LD long double
#define PR pair<int,int>

#define Fox(i,n) for (i=0; i<n; i++)
#define Fox1(i,n) for (i=1; i<=n; i++)
#define FoxI(i,a,b) for (i=a; i<=b; i++)
#define FoxR(i,n) for (i=(n)-1; i>=0; i--)
#define FoxR1(i,n) for (i=n; i>0; i--)
#define FoxRI(i,a,b) for (i=b; i>=a; i--)
#define Foxen(i,s) for (i=s.begin(); i!=s.end(); i++)
#define Min(a,b) a=min(a,b)
#define Max(a,b) a=max(a,b)
#define Sz(s) int((s).size())
#define All(s) (s).begin(),(s).end()
#define Fill(s,v) memset(s,v,sizeof(s))
#define pb push_back
#define mp make_pair
#define x first
#define y second

template<typename T> T Abs(T x) { return(x<0 ? -x : x); }
template<typename T> T Sqr(T x) { return(x*x); }

const int INF = (int)1e9;
const LD EPS = 1e-12;
const LD PI = acos(-1.0);

bool Read(int &x)
{
	char c,r=0,n=0;
	x=0;
		for(;;)
		{
			c=getchar();
				if ((c<0) && (!r))
					return(0);
				if ((c=='-') && (!r))
					n=1;
				else
				if ((c>='0') && (c<='9'))
					x=x*10+c-'0',r=1;
				else
				if (r)
					break;
		}
		if (n)
			x=-x;
	return(1);
}

int main()
{
	int T,t;
	int N,M,K;
	int i,j,k,d,ans;
	int A[5000],B[5000];
	static int dist[100][100],dyn[5001][101][2];
	Read(T);
		Fox1(t,T)
		{
			Read(N),Read(M),Read(K);
			Fill(dist,60);
				Fox(i,N)
					dist[i][i]=0;
				while (M--)
				{
					Read(i),Read(j),Read(k),i--,j--;
					Min(dist[i][j],k);
					Min(dist[j][i],k);
				}
				Fox(i,N)
					Fox(j,N)
						Fox(k,N)
							Min(dist[j][k],dist[j][i]+dist[i][k]);
				Fox(i,K)
					Read(A[i]),Read(B[i]),A[i]--,B[i]--;
				Fox(i,K)
					if (max(dist[0][A[i]],dist[0][B[i]])>INF)
					{
						ans=-1;
						goto Done;
					}
			Fill(dyn,60);
			dyn[0][0][0]=0;
				Fox(i,K)
					Fox(k,2)
						Fox(j,N)
							if ((d=dyn[i][j][k])<INF)
								if (!k) // must pick up i next
									Min(dyn[i][A[i]][1],d+dist[j][A[i]]);
								else // i already picked up
								{
									// deliver i immediately
									Min(dyn[i+1][B[i]][0],d+dist[j][B[i]]);
									// pick up i+1 and then deliver i
										if (i<K-1)
											Min(dyn[i+1][B[i]][1],d+dist[j][A[i+1]]+dist[A[i+1]][B[i]]);
								}
			ans=dyn[K][B[K-1]][0];
Done:;
			printf("Case #%d: %d\n",t,ans);
		}
	return(0);
}