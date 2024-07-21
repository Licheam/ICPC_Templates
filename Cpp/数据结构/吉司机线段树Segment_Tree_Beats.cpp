/*
    segment tree beats区间最值
    单次操作复杂度$O(\log n)$
*/
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=1000005;

struct SGT {
    //区间取min，维护最大值，严格次大值，最大值个数，最大值更新标记。
    int mx[MAXN<<2],smx[MAXN<<2],cmx[MAXN<<2],tag[MAXN<<2];
    LL sum[MAXN<<2];

    void pushup(int x) {
        sum[x]=sum[x<<1]+sum[x<<1|1];
        mx[x]=max(mx[x<<1],mx[x<<1|1]);
        if(mx[x<<1]==mx[x<<1|1]) {
            smx[x]=max(smx[x<<1],smx[x<<1|1]);
            cmx[x]=cmx[x<<1]+cmx[x<<1|1];
        } else if(mx[x<<1]>mx[x<<1|1]) {
            smx[x]=max(smx[x<<1],mx[x<<1|1]);
            cmx[x]=cmx[x<<1];
        } else {
            smx[x]=max(mx[x<<1],smx[x<<1|1]);
            cmx[x]=cmx[x<<1|1];
        }
    }

    void pushtag(int x,int d) {
        if(mx[x]<=d) return;
        sum[x]-=(1LL*mx[x]-d)*cmx[x];
        mx[x]=tag[x]=d;
    }

    void pushdown(int x) {
        if(tag[x]==-1) return;
        pushtag(x<<1,tag[x]);
        pushtag(x<<1|1,tag[x]);
        tag[x]=-1;
    }

    void build(int x,int l,int r,int *a) {
        tag[x]=-1;
        if(l==r) {
            sum[x]=mx[x]=a[l];
            smx[x]=-1;
            cmx[x]=1;
        } else {
            int m=(l+r)>>1;
            build(x<<1,l,m,a);
            build(x<<1|1,m+1,r,a);
            pushup(x);
        }
    }

    void modify_min(int x,int l,int r,int ql,int qr,int d) {
        if(mx[x]<=d) return;
        if(ql<=l && r<=qr && smx[x]<d)
            return pushtag(x,d);
        
        pushdown(x);
        int m=(l+r)>>1;
        
        if(ql<=m) modify_min(x<<1,l,m,ql,qr,d);
        if(m<qr) modify_min(x<<1|1,m+1,r,ql,qr,d);
        pushup(x);
    }

    int query_max(int x,int l,int r,int ql,int qr) {
        if(ql<=l && r<=qr) return mx[x];

        pushdown(x);
        int m=(l+r)>>1;
        int res=0;
        if(ql<=m) res=max(res,query_max(x<<1,l,m,ql,qr));
        if(m<qr) res=max(res,query_max(x<<1|1,m+1,r,ql,qr));
        return res;
    }

    LL query_sum(int x,int l,int r,int ql,int qr) {
        if(ql<=l && r<=qr) return sum[x];

        pushdown(x);
        int m=(l+r)>>1;
        LL res=0;
        if(ql<=m) res+=query_sum(x<<1,l,m,ql,qr);
        if(m<qr) res+=query_sum(x<<1|1,m+1,r,ql,qr);
        return res;
    }
}sgt;

int a[MAXN];

void solve() {
    int n,m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++)
        scanf("%d", &a[i]);
    sgt.build(1,1,n,a);
    for(int i=1;i<=m;i++) {
        int op,l,r;
        scanf("%d %d %d", &op, &l, &r);
        if(op==0) {
            int x;
            scanf("%d", &x);
            sgt.modify_min(1,1,n,l,r,x);
        } else if(op==1) {
            printf("%d\n", sgt.query_max(1,1,n,l,r));
        } else {
            printf("%lld\n", sgt.query_sum(1,1,n,l,r));
        }
    }
}

int main() {
    int T=1,cas=1;(void)(cas);
    scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}