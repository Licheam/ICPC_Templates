/*
    中国剩余定理
    x%ai=bi;
    sigma(ai*PI/ai*inv(PI/ai,ai))%PI;
*/
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=2000005;

LL exgcd(LL a,LL b,LL &x,LL &y){
    if(!b || !a){
        x=(a!=0);y=(b!=0);
        return a+b;
    }
    LL g=exgcd(b,a%b,y,x);
    y=y-(a/b)*x;
    return g;
}

LL inv(LL a,LL m) {
    LL x,y;
    exgcd(a,m,x,y);
    return (x%m+m)%m;
}

int a[MAXN],b[MAXN];

void solve() {
    int n;
    scanf("%d", &n);
    LL sum=1;
    for(int i=1;i<=n;i++) {//x%a==b
        scanf("%d %d", &a[i], &b[i]);
        sum=sum*a[i];
    }
    LL ans=0;
    for(int i=1;i<=n;i++) {
        ans=(ans+(__int128)b[i]*(sum/a[i])%sum*inv(sum/a[i],a[i])%sum)%sum;
    }
    printf("%lld\n", ans);
}