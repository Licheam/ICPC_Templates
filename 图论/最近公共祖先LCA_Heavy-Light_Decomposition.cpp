/*
	LCA重链剖分
	luogu3379
*/
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=2000005;

struct edge {
	int to,next;	
}e[MAXN<<1];

int tot,head[MAXN];

void add(int x,int y) {
	tot++;
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

int fa[MAXN],dep[MAXN],siz[MAXN],son[MAXN];
int top[MAXN],dfn[MAXN],rnk[MAXN];

void dfs1(int x,int f) {
	fa[x]=f;
	dep[x]=dep[f]+1;
	siz[x]=1;
	son[x]=0;
	for(int p=head[x];p;p=e[p].next) {
		int u=e[p].to;
		if(u==f) continue;
		dfs1(u,x);
		siz[x]+=siz[u];
		if(!son[x] || siz[u]>siz[son[x]])
			son[x]=u;
	}
}

int cnt;
void dfs2(int x,int f) {
	top[x]=f;
	dfn[x]=++cnt;
	rnk[cnt]=x;
	if(!son[x]) return;
	dfs2(son[x],f);
	for(int p=head[x];p;p=e[p].next) {
		int u=e[p].to;
		if(u==fa[x] || u==son[x]) continue;
		dfs2(u,u);
	}
}

int lca(int x,int y) {
	while(top[x]!=top[y]) {
		if(dep[top[x]]>dep[top[y]])
			x=fa[top[x]];
		else y=fa[top[y]];
	}
	if(dep[x]>dep[y]) return y;
	else return x;
}

void solve() {
	int n,m,s;
	scanf("%d %d %d", &n, &m, &s);
	tot=0;
	memset(head+1,0,n*sizeof(head[0]));
	for(int i=1;i<n;i++) {
		int f,g;
		scanf("%d %d", &f, &g);
		add(f,g);
		add(g,f);
	}
	dep[0]=0;
	dfs1(s,0);
	cnt=0;
	dfs2(s,s);

	for(int i=1;i<=m;i++) {
		int f,g;
		scanf("%d %d", &f, &g);
		printf("%d\n", lca(f,g));
	}
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