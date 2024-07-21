/*
	Link-Cut Tree luogu P3690
	询问x-y路径xor和
	连接x-y（不保证不联通）
	删除x-y（不保证存在）
	修改x权值
*/

#include <bits/stdc++.h>
#define MAXN 100005
const int inf=0x3f3f3f3f;
using namespace std;

struct LCT {
	

	int fa[MAXN],ch[MAXN][2],tag[MAXN];

	int v[MAXN],sxor[MAXN];

	bool Get(int x) {return ch[fa[x]][1]==x;}
	bool isRoot(int x) {return ch[fa[x]][0]!=x && ch[fa[x]][1]!=x;}
	void init(int x) {fa[x]=tag[x]=ch[x][0]=ch[x][1]=0;}
	void pushdown(int x) {
		if(tag[x]){
			tag[ch[x][0]]^=1;
			tag[ch[x][1]]^=1;
			swap(ch[x][0],ch[x][1]);
			tag[x]=0;
		}
	}
	void pushup(int x) {
		pushdown(x);
		sxor[x]=sxor[ch[x][0]]^sxor[ch[x][1]]^v[x];
	}

	void rotate(int x) {
		int f=fa[x], ff=fa[f],k=Get(x);
		if(!isRoot(f)) ch[ff][Get(f)]=x;

		fa[x]=ff;
		fa[ch[x][!k]]=f; ch[f][k]=ch[x][!k];
		ch[x][!k]=f; fa[f]=x;
		pushup(f); pushup(x);
	}

	void update(int x) {
		if(!isRoot(x)) update(fa[x]);
		pushdown(x);
	}

	void splay(int x) {
		update(x);
		for(int f;f=fa[x],!isRoot(x);rotate(x)){
			if(!isRoot(f))
				rotate(Get(x)==Get(f)?f:x);
		}
	}

	int access(int x) {
		int c;
		for (c=0;x;c=x,x=fa[x]) {
			splay(x);
			ch[x][1]=c;
			pushup(x);
		}
		return c;
	}

	void makeroot(int x) {
		x=access(x);
		tag[x]^=1;
	}

	int findroot(int x) {
		access(x);
		splay(x);
		pushdown(x);
		while(ch[x][0]) {
			x=ch[x][0];
			pushdown(x);
		}
		splay(x);
		return x;
	}

	void link(int x,int y) {
		makeroot(x);
		splay(x);
		if(findroot(y)==x)
			return;
		fa[x]=y;
	}

	void cut(int x,int y) {
		makeroot(x);
		access(y);
		splay(y);
		if(ch[y][0]!=x || ch[x][1]) return;
		ch[y][0]=fa[x]=0;
	}
}lct;

int a[MAXN];

int main(){
	int n,m;
	scanf("%d %d", &n, &m);
	lct.init(0);
	lct.v[0]=lct.sxor[0]=0;
	for(int i=1;i<=n;i++) {
		scanf("%d", &a[i]);
		lct.init(i);
		lct.v[i]=lct.sxor[i]=a[i];
	}

	for(int i=1;i<=m;i++) {
		int opt,x,y;
		scanf("%d %d %d", &opt, &x, &y);
		if(opt==0) {// xor(x,y);
			lct.makeroot(x);
			lct.access(y);
			lct.splay(y);
			printf("%d\n", lct.sxor[y]);
		} else if(opt==1) {
			lct.link(x,y);
		} else if(opt==2) {
			lct.cut(x,y);
		} else {
			lct.splay(x);
			lct.v[x]=y;
			lct.pushup(x);
		}
	}

	return 0;
}