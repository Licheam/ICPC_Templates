/*
	Coded with Leachim's ACM Template.
	No errors. No warnings. ~~
*/
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const LL INF=0x3f3f3f3f3f3f3f3f;
const double eps=1e-7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int RT=3;
const int MOD=998244353;
const int MAXN=20000005;

int inv[MAXN],f[MAXN],fi[MAXN];

void pre_inv(int n,int p) {
    inv[1]=1;
    f[0]=fi[0]=f[1]=fi[1]=1;
    for(int i=2;i<=n;i++) {
        inv[i]=1LL*(p-p/i)*inv[p%i]%p;
        f[i]=1LL*f[i-1]*i%p;
        fi[i]=1LL*fi[i-1]*inv[i]%p;
    }
}

void solve() {
	int n,p;
	scanf("%d %d", &n, &p);
	pre_inv(n,p);
	for(int i=1;i<=n;i++)
		printf("%d\n", inv[i]);
}

int main() {
	int T=1,cas=1;(void)(cas);
	// scanf("%d", &T);
	while(T--) {
		// printf("Case #%d: ", cas++);
		solve();
	}
	return 0;
}