#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=2000005;

//似乎会爆LL
LL c[MAXN],dp[MAXN];
LL X[MAXN],Y[MAXN];

void solve() {
	int n,L;
	scanf("%d %d", &n, &L);
	L++;
	c[0]=0;
	for(int i=1;i<=n;i++) {
		scanf("%lld", &c[i]);
		c[i]+=c[i-1]+1;//c[i] = sum(c[j])+i;
	}
	int h,t;
	h=t=1;
	dp[0]=0;
	X[t]=c[0];
	Y[t]=dp[0]+c[0]*c[0];
	for(int i=1;i<=n;i++) {
		while(h<t && Y[h+1]-Y[h]<=2*(X[h+1]-X[h])*(c[i]-L)) h++;
		dp[i]=Y[h]-2*(c[i]-L)*X[h]+(c[i]-L)*(c[i]-L);
		LL x=c[i],y=dp[i]+c[i]*c[i];
		while(h<t && (y-Y[t])*(X[t]-X[t-1])<=(Y[t]-Y[t-1])*(x-X[t])) t--;
		t++;
		X[t]=x,Y[t]=y;
	}
	printf("%lld\n", dp[n]);
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