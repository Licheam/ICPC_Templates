/*
    康托（Cantor）展开：求全排列是第几个。
*/
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=2000005;
const int MOD=998244353;

struct BIT {
    int n,b[MAXN];

    int lowbit(int x){
        return x&(-x);
    }

    void change(int x,int y){
        for(;x<=n;x+=lowbit(x))
            b[x]+=y;
    }

    int sum(int x){
        int s=0;
        for(;x>0;x-=lowbit(x))
            s+=b[x];
        return s;
    }
}bit;

int a[MAXN],f[MAXN];

void solve() {
    int n;
    scanf("%d", &n);
    for(int i=1;i<=n;i++)
        scanf("%d", &a[i]);
    
    f[0]=1;
    for(int i=1;i<=n;i++)
        f[i]=1LL*f[i-1]*i%MOD;

    bit.n=n;

    int ans=1;
    for(int i=1;i<n;i++) {
        bit.change(a[i],1);
        ans=(ans+1LL*f[n-i]*(a[i]-bit.sum(a[i]))%MOD)%MOD;
    }
    printf("%d\n", ans);
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