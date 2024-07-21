/*
    可撤销并查集+线段树分治
    离线操作：增边，删边，询问图是否联通
*/
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=5005;
const int MAXM=500005;

struct DSU{
    int fa[MAXN],rk[MAXN];
    vector<pair<int*,int>> stk;
    void init(int n) {
        stk.clear();
        for(int i=1;i<=n;i++) fa[i]=i,rk[i]=1;
    }
    int find(int x) {
        if(x==fa[x]) return x;
        return find(fa[x]);
    }
    bool join(int x,int y) {
        int rx=find(x),ry=find(y);
        if(rx==ry) return false;

        if(rk[rx]>rk[ry]) swap(rx,ry);
        stk.emplace_back(fa+rx,rx);
        fa[rx]=ry;
        stk.emplace_back(rk+ry,rk[ry]);
        rk[ry]+=rk[rx];
        return true;
    }
    void withdraw() {
        *stk.back().first=stk.back().second;
        stk.pop_back();
        *stk.back().first=stk.back().second;
        stk.pop_back();
    }
}dsu;

int qf[MAXM],qg[MAXM];

struct SGT{
    vector<pair<int,int>> eg[MAXM<<2];

    void modify(int x,int l,int r,int ql,int qr,int f,int g) {
        if(ql<=l && r<=qr) {
            eg[x].emplace_back(f,g);
            return;
        }
        int m=(l+r)>>1;
        if(ql<=m) modify(x<<1,l,m,ql,qr,f,g);
        if(m<qr) modify(x<<1|1,m+1,r,ql,qr,f,g);
    }

    void dfs(int x,int l,int r) {
        int cnt=0;
        for(auto pr:eg[x])
            if(dsu.join(pr.first,pr.second))
                cnt++;
        if(l==r) {
            if(qf[l]) printf("%c\n", "NY"[dsu.find(qf[l])==dsu.find(qg[l])]);
        } else {
            int m=(l+r)>>1;
            dfs(x<<1,l,m);
            dfs(x<<1|1,m+1,r);
        }
        while(cnt--) dsu.withdraw();
    }
}sgt;

int mp[MAXN][MAXN];

void solve() {
    int n,m;
    scanf("%d %d", &n, &m);
    memset(qf+1,0,m*sizeof(qf[0]));
    memset(qg+1,0,m*sizeof(qg[0]));
    for(int i=1;i<=m;i++) {
        int op,f,g;
        scanf("%d %d %d", &op, &f, &g);
        if(op==0) {
            mp[f][g]=mp[g][f]=i;
        } else if(op==1) {
            sgt.modify(1,1,m+1,mp[f][g],i,f,g);
            mp[f][g]=mp[g][f]=0;
        } else qf[i]=f,qg[i]=g;
    }

    for(int f=1;f<n;f++) {
        for(int g=f+1;g<=n;g++) {
            if(mp[f][g]) {
                sgt.modify(1,1,m+1,mp[f][g],m+1,f,g);
                mp[f][g]=mp[g][f]=0;
            }
        }
    }

    dsu.init(n);
    sgt.dfs(1,1,m+1);
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