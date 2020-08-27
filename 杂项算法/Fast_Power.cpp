#include <cstdio>

#define LL long long

LL a,b,n;

LL binpow(LL x,LL y,LL m){
	LL r=1%m;
	while(y){
		if(y&1)
			r=r*x%m;
		x=x*x%m;
		y>>=1;
	}
	return r;
}

int main(){
	scanf("%lld %lld %lld",&a,&b,&n);
	printf("%lld^%lld mod %lld=%lld\n",a,b,n,binpow(a,b,n));
	return 0;
}
