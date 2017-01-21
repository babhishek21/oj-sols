// Hacker Cup 2017
// Round 1
// Beach Umbrellas
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

#define MOD 1000000007

int fact[2005],ifact[2005];

PR GCD(int a,int b)
{
		if (!b)
			return(mp(1,0));
	PR p=GCD(b,a%b);
	return(mp(p.y,p.x-p.y*(a/b)));
}

int Add(int a,int b)
{
	a+=b;
		if (a>=MOD)
			a-=MOD;
	return(a);
}

int Mult(int a,int b)
{
	return((LL)a*b%MOD);
}

int Div(int a,int b)
{
	b=GCD(b,MOD).x;
		if (b<0)
			b+=MOD;
	return(Mult(a,b));
}

int Ch(int n,int k)
{
		if ((k<0) || (k>n))
			return(0);
	Min(k,n-k);
	int i,v=1;
		Fox(i,k)
			v=Mult(v,n-i);
	return(Mult(v,ifact[k]));
}

int main()
{
	int T,t;
	int N,M;
	int i,j,s;
	int ans;
	int R[2000],cnt[4001];
		Fox(i,2005)
		{
			fact[i]=i ? Mult(fact[i-1],i) : 1;
			ifact[i]=Div(1,fact[i]);
		}
	Read(T);
		Fox1(t,T)
		{
			s=ans=0;
			Read(N),Read(M);
				Fox(i,N)
					Read(R[i]),s+=R[i]*2;
				if (N==1)
				{
					ans=M;
					goto Done;
				}
			Fill(cnt,0);
				Fox(i,N)
					Fox(j,N)
						if (i!=j)
							cnt[R[i]+R[j]]++;
				Fox1(i,4000)
					if (cnt[i])
						ans=Add(ans,Mult(cnt[i],Mult(fact[N-2],Ch(M+i-s+N-1,N))));
Done:;
			printf("Case #%d: %d\n",t,ans);
		}
	return(0);
}