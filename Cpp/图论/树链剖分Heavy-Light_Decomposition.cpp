/*
	重链剖分luogu3384
	路径修改
	路径和查询
	子树修改
	子树和查询
*/
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const int MAXN=2000005;
int P;

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
	int sum[MAXN<<2],tag[MAXN<<2];

	void pushup(int x) {sum[x]=(1LL*sum[x<<1]+sum[x<<1|1])%P;}
	void pushdown(int x,int l,int r) {
		int m=(l+r)>>1;
		sum[x<<1]=(sum[x<<1]+1LL*tag[x]*(m-l+1)%P)%P;
		tag[x<<1]=(1LL*tag[x<<1]+tag[x])%P;
		sum[x<<1|1]=(sum[x<<1|1]+1LL*tag[x]*(r-m)%P)%P;
		tag[x<<1|1]=(1LL*tag[x<<1|1]+tag[x])%P;
		tag[x]=0;
	}

	void build(int x,int l,int r) {
		tag[x]=0;
		if(l==r) sum[x]=w[rnk[l]]%P;
		else {
			int m=(l+r)>>1;
			build(x<<1,l,m);
			build(x<<1|1,m+1,r);
			pushup(x);
		}
	}

	void modify(int x,int l,int r,int ql,int qr,int delta) {
		if(ql<=l && r<=qr) {
			sum[x]=(sum[x]+1LL*delta*(r-l+1)%P)%P;
			tag[x]=(1LL*tag[x]+delta)%P;
			return;
		}
		if(tag[x]) pushdown(x,l,r);
		int m=(l+r)>>1;
		if(ql<=m) modify(x<<1,l,m,ql,qr,delta);
		if(m<qr) modify(x<<1|1,m+1,r,ql,qr,delta);
		pushup(x);
	}

	int query(int x,int l,int r,int ql,int qr){
		if(ql<=l && r<=qr) return sum[x];

		if(tag[x]) pushdown(x,l,r);
		int m=(l+r)>>1;
		LL res=0;
		if(ql<=m) res=(1LL*res+query(x<<1,l,m,ql,qr))%P;
		if(m<qr) res=(1LL*res+query(x<<1|1,m+1,r,ql,qr))%P;
		return res;
	}
}sgt;

void solve() {
	int n,m,s;
	scanf("%d %d %d %d", &n, &m, &s, &P);
	tot=0;
	memset(head+1,0,n*sizeof(head[0]));
	for(int i=1;i<=n;i++)
		scanf("%d", &w[i]);
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

	sgt.build(1,1,n);

	for(int i=1;i<=m;i++) {
		int opt;
		scanf("%d", &opt);
		if(opt==1) { //w(x,y)+z;
			int x,y,z;
			scanf("%d %d %d", &x, &y, &z);
			while(top[x]!=top[y]) {
				if(dep[top[x]]>dep[top[y]]) {
					sgt.modify(1,1,n,dfn[top[x]],dfn[x],z);
					x=fa[top[x]];
				} else {
					sgt.modify(1,1,n,dfn[top[y]],dfn[y],z);
					y=fa[top[y]];
				}
			}
			if(dep[x]>dep[y]) sgt.modify(1,1,n,dfn[y],dfn[x],z);
			else sgt.modify(1,1,n,dfn[x],dfn[y],z);
		} else if(opt==2) { //sum(x,y)
			int x,y;
			scanf("%d %d", &x, &y);
			int sum=0;
			while(top[x]!=top[y]) {
				if(dep[top[x]]>dep[top[y]]) {
					sum=(1LL*sum+sgt.query(1,1,n,dfn[top[x]],dfn[x]))%P;
					x=fa[top[x]];
				} else {
					sum=(1LL*sum+sgt.query(1,1,n,dfn[top[y]],dfn[y]))%P;
					y=fa[top[y]];
				}
			}
			if(dep[x]>dep[y]) sum=(1LL*sum+sgt.query(1,1,n,dfn[y],dfn[x]))%P;
			else sum=(1LL*sum+sgt.query(1,1,n,dfn[x],dfn[y]))%P;
			printf("%d\n", sum);
		} else if(opt==3){// w(x.tree)+z
			int x,z;
			scanf("%d %d", &x, &z);
			sgt.modify(1,1,n,dfn[x],dfn[x]+siz[x]-1,z);
		} else { // sum(x.tree)
			int x;
			scanf("%d", &x);
			printf("%d\n", sgt.query(1,1,n,dfn[x],dfn[x]+siz[x]-1));
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