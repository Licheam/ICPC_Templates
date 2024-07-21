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
const LL INF=0x3f3f3f3f3f3f3f3f;
const double eps=1e-7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int MOD=1e9+9;
const int MAXN=2000005;

void FWTor(int n,int* P,int f) {
    for (int l=1;(l<<1)<=n;l<<=1)
        for(int i=0;i<n;i+=(l<<1))
            for(int j=0;j<l;j++)
                P[i+j+l]=((P[i+j+l]+P[i+j]*f)%MOD+MOD)%MOD;
}

int A[21][MAXN],B[21][MAXN],C[21][MAXN];

void solve() {
    int n;
    scanf("%d", &n);
    int lim=1<<n;
    for(int i=0;i<=n;i++) {
        memset(A[i],0,lim*sizeof(A[i][0]));
        memset(B[i],0,lim*sizeof(B[i][0]));
        memset(C[i],0,lim*sizeof(C[i][0]));
    }
    for(int i=0;i<lim;i++)
        scanf("%d", &A[__builtin_popcount(i)][i]);
    for(int i=0;i<lim;i++)
        scanf("%d", &B[__builtin_popcount(i)][i]);

    for(int i=0;i<=n;i++) {
        FWTor(lim,A[i],1);
        FWTor(lim,B[i],1);
    }

    for(int i=0;i<=n;i++) {
        for(int j=0;j<=i;j++) {
            for(int s=0;s<lim;s++) {
                C[i][s]=(C[i][s]+1LL*A[j][s]*B[i-j][s]%MOD)%MOD;
            }
        }
        FWTor(lim,C[i],-1);
    }

    for(int i=0;i<lim;i++) printf("%d ", C[__builtin_popcount(i)][i]);
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