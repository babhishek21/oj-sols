/**
 * @author babhishek21
 * @lang C++ 14 (GNU C++ 4.9.2)
 */
#include<bits/stdc++.h>

// Input macros
#define s(n)                        scanf("%d",&n)
#define sc(n)                       scanf("%c",&n)
#define sl(n)                       scanf("%lld",&n)
#define sf(n)                       scanf("%lf",&n)
#define ss(n)                       scanf("%s",n)

// Useful constants
#define INF                         (int)1e9
#define EPS                         1e-9

// Useful hardware instructions
#define bitcount                    __builtin_popcount
#define gcd                         __gcd

// Useful container manipulation / traversal macros
#define forall(i,a,b)               for(int i=a;i<b;i++)
#define foreach(v, c)               for( typeof( (c).begin()) v = (c).begin();  v != (c).end(); ++v)
#define all(a)                      a.begin(), a.end()
#define in(a,b)                     ( (b).find(a) != (b).end())
#define pb                          push_back
#define fill(a,v)                   memset(a, v, sizeof a)
#define sz(a)                       ((int)(a.size()))
#define mp                          make_pair
#define fi                          first
#define se                          second

// iteration macros: have advantage of auto-casting and not recomputing arguments
#define rep(i,n)                    for(int i=0, _##i=(n); i<_##i; ++i)
#define dwn(i,n)                    for(int i=(n); --i>=0; )
#define repr(i,l,r) for(int i=(l), _##i=(r); i<_##i; ++i)
#define dwnr(i,l,r) for(int i=(r), _##i=(l); --i>=_##i; )
#define repi(i,a) for(__typeof((a).begin()) i=(a).begin(), _##i=(a).end(); i!=_##i; ++i)
#define dwni(i,a) for(__typeof((a).rbegin()) i=(a).rbegin(), _##i=(a).rend(); i!=_##i; ++i)

// debug macro that prints out "expression: value" for clarity
#define debug(args...) do {cerr << #args << ": "; dbg,args; cerr << endl;} while(0)

// Some common useful functions
#define checkbit(n,b)                ( (n >> b) & 1)
#define DREP(a)                      sort(all(a)); a.erase(unique(all(a)),a.end())
#define INDEX(arr,ind)               (lower_bound(all(arr),ind)-arr.begin())

using namespace std;

// directions
const int fx[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
const int fxx[8][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};

// globals
int N, arr[2000], dp[2000][2000] = {0}; //placing on heap

int main() {

    s(N);

    rep(i,N) {
        s(arr[i]);
        dp[i][i] = N*arr[i]; // (i,i) has guaranteed age of N
    }

    // dp approach
    dwn(i,N-1) { // go down from second last element
        repr(j,i+1,N) {
            int time = N-(j-i);
            dp[i][j] = max( dp[i+1][j] + time*arr[i],
                           dp[i][j-1] + time*arr[j] );
        }
    }

    printf("%d\n", dp[0][N-1]);

    return 0;
}
