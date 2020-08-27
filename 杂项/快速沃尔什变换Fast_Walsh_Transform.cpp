/*
    Coded with Leachim's ACM Template.
    No errors. No warnings. ~~
*/
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int MAXN=2000005;
const int MOD=998244353;

void FWTor(int n,int* P,int f) {
    for (int l=1;(l<<1)<=n;l<<=1)
        for(int i=0;i<n;i+=(l<<1))
            for(int j=0;j<l;j++)
                P[i+j+l]=((P[i+j+l]+P[i+j]*f)%MOD+MOD)%MOD;
}

void FWTand(int n,int* P,int f) {
    for (int l=1;(l<<1)<=n;l<<=1)
        for(int i=0;i<n;i+=(l<<1))
            for(int j=0;j<l;j++)
                P[i+j]=((P[i+j]+P[i+j+l]*f)%MOD+MOD)%MOD;
}

void FWTxor(int n,int* P,int f) {
    for (int l=1;(l<<1)<=n;l<<=1)
        for(int i=0;i<n;i+=(l<<1))
            for(int j=0;j<l;j++) {
                int t=P[i+j];
                P[i+j]=(1LL*f*(t+P[i+j+l])%MOD+MOD)%MOD;
                P[i+j+l]=(1LL*f*(t-P[i+j+l])%MOD+MOD)%MOD;
            }
}

int A[MAXN],B[MAXN],C[MAXN];

void solve() {
    int n;
    scanf("%d", &n);
    int lim=1<<n;
    for(int i=0;i<lim;i++) scanf("%d", &A[i]);
    for(int i=0;i<lim;i++) scanf("%d", &B[i]);

    FWTor(lim,A,1);FWTor(lim,B,1);
    for(int i=0;i<lim;i++) C[i]=1LL*A[i]*B[i]%MOD;
    FWTor(lim,A,-1);FWTor(lim,B,-1);FWTor(lim,C,-1);
    for(int i=0;i<lim;i++) printf("%d ", C[i]);
    puts("");

    FWTand(lim,A,1);FWTand(lim,B,1);
    for(int i=0;i<lim;i++) C[i]=1LL*A[i]*B[i]%MOD;
    FWTand(lim,A,-1);FWTand(lim,B,-1);FWTand(lim,C,-1);
    for(int i=0;i<lim;i++) printf("%d ", C[i]);
    puts("");

    FWTxor(lim,A,1);FWTxor(lim,B,1);
    for(int i=0;i<lim;i++) C[i]=1LL*A[i]*B[i]%MOD;
    FWTxor(lim,A,(MOD+1)/2);FWTxor(lim,B,(MOD+1)/2);FWTxor(lim,C,(MOD+1)/2);
    for(int i=0;i<lim;i++) printf("%d ", C[i]);
    puts("");
}

int main() {
    int T=1,cas=1;(void)(cas);
    // scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}