#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=2000005;

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