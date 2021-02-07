/*
    Pollard_Rho分解因数，要保证放入的为合数。
    期望复杂度O(n^(1/4))，要随机化。
*/
#include <bits/stdc++.h>
#define LL long long
using namespace std;

LL gcd(LL x,LL y) {
    if(!x || !y) return x+y;
    return gcd(y,x%y);
}

LL binpow(LL x,LL y,LL m) {
    LL r=1%m;
    while(y) {
        if(y&1) r=(__int128)r*x%m;
        x=(__int128)x*x%m;
        y>>=1;
    }
    return r;
}

bool Miller_Rabin(LL x) {
    if(x==1) return false;

    const int p[9]={2,3,5,7,11,13,17,19,23};
    for(int i=0;i<9;i++) {
        if(x==p[i]) return true;

        LL t=x-1;
        while(!(t&1)) t>>=1;
        LL a=binpow(p[i],t,x),lst;
        while(t!=x-1) {
            lst=a;
            a=(__int128)a*a%x;
            t<<=1;
            if(a==1 && lst!=x-1 && lst!=1) return false;
        }
        if(a!=1) return false;
    }
    return true;
}

LL f(LL x,LL c,LL m) {return ((__int128)x*x+c)%m;}

LL Pollard_Rho(LL x) {
    if(x==1) return x;

    LL c=rand()%(x-1)+1;
    LL s=0,t=0,val=1;
    for(int goal=1;;goal<<=1,s=t,val=1) {
        for(int step=1;step<=goal;step++) {
            t=f(t,c,x);
            val=(__int128)val*abs(t-s)%x;
            if(step%127==0) {
                LL g=gcd(val,x);
                if(g>1) return g;
            }
        }
        LL g=gcd(val,x);
        if(g>1) return g;
    }
}

LL max_factor(LL x) {
    if(x==1 || Miller_Rabin(x)) {
        return x;
    } else {
        LL g=Pollard_Rho(x);
        while(x%g==0) x/=g;
        return max(max_factor(x),max_factor(g));
    }
}

void solve() {
    LL n;
    scanf("%lld", &n);
    if(Miller_Rabin(n)) {
        printf("Prime\n");
    } else {
        printf("%lld\n", max_factor(n));
    }
}

int main() {
    srand(time(0));
    int T=1,cas=1;(void)(cas);
    scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}