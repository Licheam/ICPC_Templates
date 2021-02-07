#include <cstdio>
#define LL long long

LL n;

int main(){
    scanf("%lld", &n);
    LL ans=0;
    for(LL i=1;i<=n;i++){
        LL t=n/i,j=n/t;
        ans+=(j-i+1)*t;
        i=j;
    }
    printf("%lld\n", ans);
    return 0;
}