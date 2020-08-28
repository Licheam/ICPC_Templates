#include <cstdio>
#define LL long long
#define MAXP 100005

int inv[MAXP];
int f[MAXP],fi[MAXP];

void pre(LL p){
    inv[1]=1;
    f[0]=fi[0]=f[1]=fi[1]=1;
    for(int i=2;i<=p-1;i++) {
        inv[i]=1LL*(p-p/i)*inv[p%i]%p;
        f[i]=1LL*f[i-1]*i%p;
        fi[i]=1LL*fi[i-1]*inv[i]%p;
    }
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