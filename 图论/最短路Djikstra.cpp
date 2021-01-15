#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const LL INF=0x3f3f3f3f3f3f3f3f;
const int MOD=998244353;
const int MAXN=2000005;

struct edge {
	int to,next,w;
}e[MAXN<<1];

int tot,head[MAXN];

void add(int x,int y,int z) {
	tot++;
	e[tot].to=y;
	e[tot].w=z;
	e[tot].next=head[x];
	head[x]=tot;
}

struct node {
	int u;
	LL dis;
	bool operator<(const node& y) const{
		return dis>y.dis;
	}
};

LL dist[MAXN];
bool flag[MAXN];
priority_queue<node> Q;

void dij(int n,int s) {
	memset(flag+1,0,n*sizeof(flag[0]));
	memset(dist+1,0x3f,n*sizeof(dist[0]));
	dist[s]=0;
	Q.push({s,0LL});
	while(!Q.empty()) {
		while(!Q.empty() && flag[Q.top().u]) Q.pop();
		if(Q.empty()) break;
		int u=Q.top().u;
		Q.pop();
		flag[u]=1;
		for(int p=head[u];p;p=e[p].next) {
			int v=e[p].to,w=e[p].w;
			if(flag[v]) continue;
			if(dist[u]+w<dist[v]) {
				dist[v]=dist[u]+w;
				Q.push({v,dist[v]});
			}
		}
	}
}

void solve() {
	int n,m,s;
	scanf("%d %d %d", &n, &m, &s);
	tot=0;
	memset(head+1,0,n*sizeof(head[0]));
	for(int i=1;i<=m;i++) {
		int f,g,w;
		scanf("%d %d %d", &f, &g, &w);
		add(f,g,w);
	}
	dij(n,s);
	for(int i=1;i<=n;i++)
		printf("%lld%c", dist[i], " \n"[i==n]);
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