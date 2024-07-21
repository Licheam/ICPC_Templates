#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=100005;
const int MOD=571373;

struct SGT{
    LL sum[MAXN<<2],ts[MAXN<<2],tm[MAXN<<2];
    
    void pushup(int x) {sum[x]=(sum[x<<1]+sum[x<<1|1])%MOD;}
    void pushdown(int x,int l,int r) {
        int m=(l+r)>>1;
        sum[x<<1]=(sum[x<<1]*tm[x]%MOD + ts[x]*(m-l+1)%MOD)%MOD;
        sum[x<<1|1]=(sum[x<<1|1]*tm[x]%MOD + ts[x]*(r-m)%MOD)%MOD;
        tm[x<<1]=tm[x<<1]*tm[x]%MOD;
        tm[x<<1|1]=tm[x<<1|1]*tm[x]%MOD;
        ts[x<<1]=(ts[x<<1]*tm[x]%MOD+ts[x])%MOD;
        ts[x<<1|1]=(ts[x<<1|1]*tm[x]%MOD+ts[x])%MOD;
        tm[x]=1;
        ts[x]=0;
    }
    
    void build(int x,int l,int r,LL* a) {
        ts[x]=0,tm[x]=1;
        if(l==r) sum[x]=a[l];
        else {
            int m=(l+r)>>1;
            build(x<<1,l,m,a);
            build(x<<1|1,m+1,r,a);
            pushup(x);
        }
    }
    
    void plus(int x,int l,int r,int ql,int qr,LL d) {
        if(ql<=l && r<=qr) {
            sum[x]=(sum[x]+d*(r-l+1)%MOD)%MOD;
            ts[x]=(ts[x]+d)%MOD;
            return;
        }

        pushdown(x,l,r);
        int m=(l+r)>>1;
        if(ql<=m) plus(x<<1,l,m,ql,qr,d);
        if(m<qr) plus(x<<1|1,m+1,r,ql,qr,d);
        pushup(x);
    }
    
    void multi(int x,int l,int r,int ql,int qr,LL d) {
        if(ql<=l && r<=qr) {
            sum[x]=(sum[x]*d)%MOD;
            ts[x]=(ts[x]*d)%MOD;
            tm[x]=(tm[x]*d)%MOD;
            return;
        }

        pushdown(x,l,r);
        int m=(l+r)>>1;
        if(ql<=m) multi(x<<1,l,m,ql,qr,d);
        if(m<qr) multi(x<<1|1,m+1,r,ql,qr,d);
        pushup(x);
    }

    LL query(int x,int l,int r,int ql,int qr) {
        if(ql<=l && r<=qr) {
            return sum[x];
        }

        pushdown(x,l,r);
        int m=(l+r)>>1;
        LL res=0;
        if(ql<=m) res=(res+query(x<<1,l,m,ql,qr))%MOD;
        if(m<qr) res=(res+query(x<<1|1,m+1,r,ql,qr))%MOD;
        return res;
    }
}sgt;

LL a[MAXN];

int main(){
    int n,m,p;
    scanf("%d %d %d", &n, &m, &p);
    for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
    sgt.build(1,1,n,a);
    for(int i=1;i<=m;i++){
        int op,l,r;
        scanf("%d", &op);
        if(op==1){
            LL k;
            scanf("%d %d %lld", &l, &r, &k);
            sgt.multi(1,1,n,l,r,k);
        } else if(op==2) {
            LL k;
            scanf("%d %d %lld", &l, &r, &k);
            sgt.plus(1,1,n,l,r,k);
        } else {
            scanf("%d %d",&l,&r);
            printf("%lld\n", sgt.query(1,1,n,l,r));
        }
    }
    return 0;
}