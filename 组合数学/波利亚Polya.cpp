/*
	Polya定理
	本质不同个数=sigma(颜色个数^等价置换的划分个数)/(等价置换总个数)

	例题：n条个点围成一圈，m种颜色。求染色旋转本质不同个数。
	ans = $\frac1n\sum\limits_{i=1}^n(m^{\gcd(n,i)})$
		= $\frac1n\sum\limits_{d|n}(m^d\varphi(\frac{n}{d}))$  ----- 莫比乌斯反演
*/
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MOD=1e9+7;
const int MAXN=2000005;

int binpow(int x,int y,int m) {
	int r=1%m;
	while(y) {
		if(y&1) r=1LL*r*x%m;
		x=1LL*x*x%m;
		y>>=1;
	}
	return r;
}

int phi(int x) {
	int r=x;
	for(int i=2;i*i<=x;i++) {
		if(x%i==0) {
			r=r/i*(i-1);
			while(x%i==0) x/=i;
		}
	}
	if(x>1) r=r/x*(x-1);
	return r;
}

void solve() {
	int n,m; //n个点，m种颜色。
	scanf("%d", &n);
	m=n;
	int ans=0;
	for(int i=1;i*i<=n;i++) {
		if(n%i==0) {
			ans=(ans+1LL*binpow(m,i,MOD)*phi(n/i)%MOD)%MOD;
			if(i*i!=n) {
				ans=(ans+1LL*binpow(m,n/i,MOD)*phi(i)%MOD)%MOD;
			}
		}
	}
	ans=1LL*ans*binpow(n,MOD-2,MOD)%MOD;
	printf("%d\n", ans);
}

int main() {
	int T=1,cas=1;(void)(cas);
	scanf("%d", &T);
	while(T--) {
		// printf("Case #%d: ", cas++);
		solve();
	}
	return 0;
}