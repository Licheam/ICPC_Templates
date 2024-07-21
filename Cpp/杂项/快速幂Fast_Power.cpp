#include <cstdio>

#define LL long long

LL a,b,n;

#include <cstdio>

#define LL long long

LL a,b,n;

LL binpow(LL x,LL y,LL m){
	LL r=1%m;
	for(;y;y>>=1,x=x*x%m)
		if(y&1) r=r*x%m;
	return r;
}

int main(){
	scanf("%lld %lld %lld",&a,&b,&n);
	printf("%lld^%lld mod %lld=%lld\n",a,b,n,binpow(a,b,n));
	return 0;
}


int main(){
	scanf("%lld %lld %lld",&a,&b,&n);
	printf("%lld^%lld mod %lld=%lld\n",a,b,n,binpow(a,b,n));
	return 0;
}
