#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=2000005;

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

    void build(int len,int *a) {
        n=len;
        for(int i=1;i<=n;i++)
            b[i]=a[i];
        for(int x=1;x<<1<=n;x<<=1)
            for(int i=x;i+x<=n;i+=x<<1)
                b[i+x]+=b[i];
    }
}bit;

int a[MAXN];

void solve() {
    int n,m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++)
        scanf("%d", &a[i]);
    bit.build(n,a);
    for(int i=1;i<=m;i++) {
        int opt,x,y;
        scanf("%d %d %d", &opt, &x, &y);
        if(opt==1) {
            bit.change(x,y);
        } else {
            printf("%d\n", bit.sum(y)-bit.sum(x-1));
        }
    }
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