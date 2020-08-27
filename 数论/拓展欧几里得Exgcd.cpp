#include <cstdio>
#include <cmath>
#define LL long long

LL exgcd(LL a,LL b,LL &x,LL &y){
	if(!b || !a){
		x=(a!=0);y=(b!=0);
		return a+b;
	}
	LL g=exgcd(b,a%b,y,x);
	y=y-(a/b)*x;
	return g;
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		LL a,b,c,x,y,g;
		scanf("%lld %lld %lld", &a, &b, &c);
		g=exgcd(a,b,x,y);
		if(c%g){
			printf("-1\n");
			continue;
		}
		a/=g;b/=g;c/=g;x*=c;y*=c;
		LL kl=ceil((double)(-x+1)/b),kr=floor((double)(y-1)/a);
		if(kr<kl){
			printf("%lld %lld\n",(x+kl*b),(y-kr*a));
		}
		else{
			printf("%lld %lld %lld %lld %lld\n",kr-kl+1,(x+kl*b),(y-kr*a),(x+kr*b),(y-kl*a));
		}
	}
	return 0;
}