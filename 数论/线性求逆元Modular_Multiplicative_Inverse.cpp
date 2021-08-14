#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=20000005;

int inv[MAXN],f[MAXN],fi[MAXN];

void pre_inv(int n,int p) {
    inv[1]=1;
    f[0]=fi[0]=f[1]=fi[1]=1;
    for(int i=2;i<=n;i++) {
        inv[i]=1LL*(p-p/i)*inv[p%i]%p;
        f[i]=1LL*f[i-1]*i%p;
        fi[i]=1LL*fi[i-1]*inv[i]%p;
    }
}

int main() {
    int n,p;
    scanf("%d %d", &n, &p);
    pre_inv(n,p);
    for(int i=1;i<=n;i++)
        printf("%d\n", inv[i]);
    
    return 0;
}