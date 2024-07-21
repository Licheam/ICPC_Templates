#include <cstdio>
#define LL long long
#define MAXP 100005

int f[MAXP],fi[MAXP];

LL binpow(LL x,LL y,LL m){
    LL r=1%m;
    for(;y;y>>=1,x=x*x%m)
        if(y&1) r=r*x%m;
    return r;
}

void pre(LL p){
    f[0]=1;
    for(int i=1;i<=p-1;i++)
        f[i]=1LL*f[i-1]*i%p;
    fi[p-1]=binpow(f[p-1],p-2,p);
    for(int i=p-1;i;i--)
        fi[i-1]=1LL*fi[i]*i%p;
}

LL C(LL x,LL y,LL p) {
    if(x<y) return 0;
    return 1LL*f[x]*fi[y]%p*fi[x-y]%p;
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