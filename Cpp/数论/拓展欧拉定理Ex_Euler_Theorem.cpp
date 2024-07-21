#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define MAXN 100000005

LL binpow(LL x,LL y,LL m){
    int r=1%m;
    x%=m;
    while(y){
        if(y&1) r=1LL*r*x%m;
        x=1LL*x*x%m;
        y>>=1;
    }
    return r;
}

void solve() {
    int a,m;
    scanf("%d %d", &a, &m);
    int mm=m,phi=m;
    for(int i=2;i*i<=m;i++) {
        if(mm%i==0){
            while(mm%i==0) mm/=i;
            phi=phi/i*(i-1);
        }
    }
    if(mm>1) phi=phi/mm*(mm-1);
    char c;
    while(!isdigit(c=getchar()));
    int b=c-'0';
    bool flag=0;
    while(isdigit(c=getchar())){
        b=10*b+c-'0';
        if(b>=phi) b%=phi, flag=1;
    }
    if(flag) b+=phi;
    printf("%lld\n", binpow(a,b,m));

}

int main() {
    int T=1;
    // scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}