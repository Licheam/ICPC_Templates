#include <cstdio>
#define LL long long
#define MAXP 100005

LL f[MAXP];

LL binpow(LL x,LL y,LL mod){
	LL r=1%mod;
	for(;y;y>>=1){
		if(y&1) r=r*x%mod;
		x=x*x%mod;
	}
	return r;
}

void pre(LL p){
	f[0]=1;
	for(int i=1;i<=p-1;i++) f[i]=f[i-1]*i%p;
}

LL C(LL x,LL y,LL p){
	if(x<y) return 0;
	return f[x]*binpow(f[y],p-2,p)%p*binpow(f[x-y],p-2,p)%p;
}

LL lucas(LL x,LL y,LL p){
	if(!y) return 1;
	return C(x%p,y%p,p)*lucas(x/p,y/p,p)%p;
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		LL n,m,p;
		scanf("%lld %lld %lld", &n, &m, &p);
		pre(p);
		printf("%lld\n", lucas(n+m,m,p));
	}
	return 0;
}