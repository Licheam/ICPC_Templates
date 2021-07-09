/*
	重链剖分
	单点修改
	路径最值
	路径和
*/
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
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
int w[MAXN];

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

struct SGT{
	LL sum[MAXN<<2];
	int mx[MAXN<<2];

	void pushup(int x) {sum[x]=sum[x<<1]+sum[x<<1|1];mx[x]=max(mx[x<<1],mx[x<<1|1]);}

	void build(int x,int l,int r) {
		if(l==r) sum[x]=mx[x]=w[rnk[l]];
		else {
			int m=(l+r)>>1;
			build(x<<1,l,m);
			build(x<<1|1,m+1,r);
			pushup(x);
		}
	}

	void modify(int x,int l,int r,int qx,int v) {
		if(l==qx && r==qx) {
			sum[x]=v;
			mx[x]=v;
			return;
		}
		int m=(l+r)>>1;
		if(qx<=m) modify(x<<1,l,m,qx,v);
		if(m<qx) modify(x<<1|1,m+1,r,qx,v);
		pushup(x);
	}

	LL qsum(int x,int l,int r,int ql,int qr) {
		if(ql<=l && r<=qr) return sum[x];

		int m=(l+r)>>1;
		LL res=0;
		if(ql<=m) res+=qsum(x<<1,l,m,ql,qr);
		if(m<qr) res+=qsum(x<<1|1,m+1,r,ql,qr);
		return res;
	}

	int qmax(int x,int l,int r,int ql,int qr) {
		if(ql<=l && r<=qr) return mx[x];

		int m=(l+r)>>1;
		int res=-inf;
		if(ql<=m) res=max(res,qmax(x<<1,l,m,ql,qr));
		if(m<qr) res=max(res,qmax(x<<1|1,m+1,r,ql,qr));
		return res;
	}
}sgt;

void solve() {
	int n;
	scanf("%d", &n);
	tot=0;
	memset(head+1,0,n*sizeof(head[0]));
	for(int i=1;i<n;i++) {
		int f,g;
		scanf("%d %d", &f, &g);
		add(f,g);
		add(g,f);
	}
	for(int i=1;i<=n;i++)
		scanf("%d", &w[i]);
	dep[0]=0;
	dfs1(1,0);
	cnt=0;
	dfs2(1,1);

	sgt.build(1,1,n);

	int q;
	scanf("%d", &q);
	for(int i=1;i<=q;i++) {
		char opt[10];
		int x,y;
		scanf("%s %d %d", opt, &x, &y);
		if(opt[0]=='C') { //w[x]=y;
			w[x]=y;
			sgt.modify(1,1,n,dfn[x],y);
		} else if(opt[1]=='M') { //max(x,y)
			int mx=-inf;
			while(top[x]!=top[y]) {
				if(dep[top[x]]>dep[top[y]]) {
					mx=max(mx,sgt.qmax(1,1,n,dfn[top[x]],dfn[x]));
					x=fa[top[x]];
				} else {
					mx=max(mx,sgt.qmax(1,1,n,dfn[top[y]],dfn[y]));
					y=fa[top[y]];
				}
			}
			if(dep[x]>dep[y]) mx=max(mx,sgt.qmax(1,1,n,dfn[y],dfn[x]));
			else mx=max(mx,sgt.qmax(1,1,n,dfn[x],dfn[y]));
			printf("%d\n", mx);
		} else {// sum(x,y);
			LL sum=0;
			while(top[x]!=top[y]) {
				if(dep[top[x]]>dep[top[y]]) {
					sum+=sgt.qsum(1,1,n,dfn[top[x]],dfn[x]);
					x=fa[top[x]];
				} else {
					sum+=sgt.qsum(1,1,n,dfn[top[y]],dfn[y]);
					y=fa[top[y]];
				}
			}
			if(dep[x]>dep[y]) sum+=sgt.qsum(1,1,n,dfn[y],dfn[x]);
			else sum+=sgt.qsum(1,1,n,dfn[x],dfn[y]);
			printf("%lld\n", sum);
		}
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