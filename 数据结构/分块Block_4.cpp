#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define LL long long
#define MAXN 50005
#define MAXB 505

using namespace std;

int n,blo;
LL v[MAXN],bl[MAXN],atag[MAXB],sum[MAXB];

void add(int l,int r,int x){
    if(bl[l]==bl[r]){
        for(int i=l;i<=r;i++)
            v[i]+=x,sum[bl[i]]+=x;
    }
    else{
        for(int i=l;i<=bl[l]*blo;i++)
            v[i]+=x,sum[bl[i]]+=x;
        for(int i=(bl[r]-1)*blo+1;i<=r;i++)
            v[i]+=x,sum[bl[i]]+=x;
        for(int i=bl[l]+1;i<=bl[r]-1;i++)
            atag[i]+=x;
    }
}

LL query(int l,int r){
    LL ans=0;
    if(bl[l]==bl[r]){
        for(int i=l;i<=r;i++)
            ans+=v[i]+atag[bl[i]];
    }
    else{
        for(int i=l;i<=bl[l]*blo;i++)
            ans+=v[i]+atag[bl[i]];
        for(int i=(bl[r]-1)*blo+1;i<=r;i++)
            ans+=v[i]+atag[bl[i]];
        for(int i=bl[l]+1;i<=bl[r]-1;i++)
            ans+=sum[i]+atag[i]*blo;
    }
    return ans;
}

int main(){
    scanf("%d", &n);blo=sqrt(n);
    for(int i=1;i<=n;i++)
        bl[i]=(i-1)/blo+1;
    memset(atag+1,0,bl[n]*sizeof(atag[0]));
    memset(sum+1,0,bl[n]*sizeof(sum[0]));
    for(int i=1;i<=n;i++){
        scanf("%lld", &v[i]);
        sum[bl[i]]+=v[i];
    }
    for(int i=1;i<=n;i++){
        int opt,l,r,c;
        scanf("%d %d %d %d", &opt, &l, &r, &c);
        if(opt==0){
            add(l,r,c);
        }
        else printf("%lld\n", query(l,r)%(c+1));
    }
    return 0;
}