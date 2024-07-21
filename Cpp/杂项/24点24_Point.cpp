/*
    Coded with Leachim's ACM Template.
    No errors. No warnings. ~~
*/
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const LL INF=0x3f3f3f3f3f3f3f3f;
const double eps=1e-7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int MOD=998244353;
const int MAXN=2000005;

int a[5],p[5];

set<pair<double,string>> dfs(int l, int r) {
    set<pair<double,string>> s;
    if(l==r) {
        s.emplace(a[p[l]],to_string(a[p[l]]));
    }
    for(int i=l;i<r;i++) {
        auto s1=dfs(l,i);
        auto s2=dfs(i+1,r);
        for(auto p1:s1) {
            for(auto p2:s2) {
                s.emplace(p1.first+p2.first,"("+p1.second+"+"+p2.second+")");
                s.emplace(p1.first-p2.first,"("+p1.second+"-"+p2.second+")");
                s.emplace(p1.first*p2.first,"("+p1.second+"*"+p2.second+")");
                if(abs(p2.first)>eps) s.emplace(p1.first/p2.first,"("+p1.second+"/"+p2.second+")");
            }
        }
    }
    return s;
}

void solve() {
    for(int i=1;i<=4;i++) {
        scanf("%d", &a[i]);
        p[i]=i;
    }
    do {
        auto s=dfs(1,4);
        for(auto p:s) {
            if(abs(p.first-24)<eps) {
                cout<<p.second.substr(1,p.second.size()-2)<<endl;
                return;
            }
        }
    }while(next_permutation(p+1,p+5));
    
    printf("-1\n");
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