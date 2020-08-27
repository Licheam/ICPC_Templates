#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MAXN 50005

using namespace std;

int n,blo,v[MAXN],bl[MAXN],atag[MAXN];

void add(int l,int r,int x){
    if(bl[l]==bl[r]){
        for(int i=l;i<=r;i++)
            v[i]+=x;
    }
    else{
        for(int i=l;i<=bl[l]*blo;i++)
            v[i]+=x;
        for(int i=(bl[r]-1)*blo+1;i<=r;i++)
            v[i]+=x;
    }
    for(int i=bl[l]+1;i<=bl[r]-1;i++)
        atag[i]+=x;
}

int main(){
    scanf("%d", &n);blo=sqrt(n);
    for(int i=1;i<=n;i++)
        scanf("%d", &v[i]);
    for(int i=1;i<=n;i++)
        bl[i]=(i-1)/blo+1;
    memset(atag+1,0,bl[n]*sizeof(atag[0]));
    for(int i=1;i<=n;i++){
        int opt,l,r,c;
        scanf("%d %d %d %d", &opt, &l, &r, &c);
        if(opt==0){
            add(l,r,c);
        }
        else printf("%d\n", v[r]+atag[bl[r]]);
    }
    return 0;
}