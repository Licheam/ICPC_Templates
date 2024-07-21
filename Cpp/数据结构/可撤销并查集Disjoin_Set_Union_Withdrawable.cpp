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