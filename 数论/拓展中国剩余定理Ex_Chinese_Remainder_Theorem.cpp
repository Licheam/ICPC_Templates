/*
    拓展中国剩余定理
    x%ai=bi;
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

LL a[MAXN],b[MAXN];

void solve() {
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++) {//x%a==b
        scanf("%lld %lld", &a[i], &b[i]);
    }

    LL M=a[1],R=b[1];//通解 R+C*M，特解 R
    for(int i=2;i<=n;i++) {
        LL x,y;
        LL g=exgcd(M,a[i],x,y);//R' = R+M*x=y*a[i]+b
        if(abs(b[i]-R)%g) {
            printf("-1\n");
            return;
        }
        x=((__int128)(b[i]-R)/g*x%(a[i]/g)+a[i]/g)%(a[i]/g);
        R=R+M*x;
        M=M/g*a[i];
    }
    printf("%lld\n", R);
}