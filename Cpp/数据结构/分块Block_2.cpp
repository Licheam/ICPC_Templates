#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#define MAXN 50005
#define MAXB 505

using namespace std;

int n,blo,v[MAXN],bl[MAXN],atag[MAXB];
vector<int> ve[MAXB];

void reset(int x){
    ve[x].clear();
    for(int i=(x-1)*blo+1;i<=min(x*blo,n);i++){
        ve[x].push_back(v[i]);
    }
    sort(ve[x].begin(),ve[x].end());
}

void add(int l,int r,int x){
    if(bl[l]==bl[r]){
        for(int i=l;i<=r;i++)
            v[i]+=x;
        reset(bl[l]);
    }
    else{
        for(int i=l;i<=bl[l]*blo;i++)
            v[i]+=x;
        reset(bl[l]);
        for(int i=(bl[r]-1)*blo+1;i<=r;i++)
            v[i]+=x;
        reset(bl[r]);
        for(int i=bl[l]+1;i<=bl[r]-1;i++)
        atag[i]+=x;
    }
}

int query(int l,int r,int x){
    int cnt=0;
    if(bl[l]==bl[r]){
        for(int i=l;i<=r;i++)
            if(v[i]+atag[bl[i]]<x) cnt++;
    }
    else{
        for(int i=l;i<=bl[l]*blo;i++)
            if(v[i]+atag[bl[i]]<x) cnt++;
        for(int i=(bl[r]-1)*blo+1;i<=r;i++)
            if(v[i]+atag[bl[i]]<x) cnt++;
        for(int i=bl[l]+1;i<=bl[r]-1;i++)
            cnt+=lower_bound(ve[i].begin(),ve[i].end(),x-atag[i])-ve[i].begin();
    }
    return cnt;
}

int main(){
    scanf("%d", &n);blo=sqrt(n);
    for(int i=1;i<=n;i++)
        scanf("%d", &v[i]);
    for(int i=1;i<=n;i++){
        bl[i]=(i-1)/blo+1;
        ve[bl[i]].push_back(v[i]);
    }
    memset(atag+1,0,bl[n]*sizeof(atag[0]));
    for(int i=1;i<=bl[n];i++)
        sort(ve[i].begin(),ve[i].end());

    for(int i=1;i<=n;i++){
        int opt,l,r,c;
        scanf("%d %d %d %d", &opt, &l, &r, &c);
        if(opt==0){
            add(l,r,c);
        }
        else{
            printf("%d\n", query(l,r,c*c));
        }
    }
    return 0;
}