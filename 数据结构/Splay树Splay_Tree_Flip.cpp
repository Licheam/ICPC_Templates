#include <cstdio>
#include <algorithm>
#define MAXN 100005
const int inf=0x3f3f3f3f;

using namespace std;

int root,len,a[MAXN];

struct node{
	int v,fa,ch[2],size,cnt,tag;
}sp[MAXN];

int getch(int x) {return sp[sp[x].fa].ch[1]==x;}
void pushup(int x) {sp[x].size=sp[x].cnt+sp[sp[x].ch[0]].size+sp[sp[x].ch[1]].size;}

void pushdown(int x){
	if(sp[x].tag){
		sp[sp[x].ch[0]].tag^=1;
		sp[sp[x].ch[1]].tag^=1;
		swap(sp[x].ch[0],sp[x].ch[1]);
		sp[x].tag=0;
	}
}

void rotate(int x){
	int f=sp[x].fa, ff=sp[f].fa;
	int k=getch(x);
	sp[ff].ch[getch(f)]=x; sp[x].fa=ff;
	sp[sp[x].ch[k^1]].fa=f; sp[f].ch[k]=sp[x].ch[k^1];
	sp[x].ch[k^1]=f; sp[f].fa=x;
	pushup(f); pushup(x);
}

void splay(int x,int goal=0){
	for(int f;(f=sp[x].fa)!=goal;rotate(x)){
		if(sp[f].fa!=goal)
			rotate(getch(x)==getch(f)?f:x);
	}
	if(!goal) root=x;
}

int find(int x){
	int cur=root;
	while(1){
		pushdown(cur);
		if(x<=sp[sp[cur].ch[0]].size)
			cur=sp[cur].ch[0];
		else if(x>sp[sp[cur].ch[0]].size+sp[cur].cnt){
			x-=sp[sp[cur].ch[0]].size+sp[cur].cnt;
			cur=sp[cur].ch[1];
		}
		else return cur;
	}
}

int built(int f,int l,int r){
	if(l>r) return 0;
	int mid=(l+r)>>1, cur=++len;
	sp[cur].fa=f;
	sp[cur].cnt=1;
	sp[cur].v=a[mid];
	sp[cur].tag=0;
	sp[cur].ch[0]=built(cur,l,mid-1);
	sp[cur].ch[1]=built(cur,mid+1,r);
	pushup(cur);
	return cur;
}

void flip(int l,int r){
	int last=find(l-1),next=find(r+1);
	splay(last);splay(next,last);
	sp[sp[sp[root].ch[1]].ch[0]].tag^=1;
}

void dfs(int cur){
	pushdown(cur);
	if(sp[cur].ch[0]) dfs(sp[cur].ch[0]);
	if(sp[cur].v!=-inf && sp[cur].v!=inf) printf("%d ", sp[cur].v);
	if(sp[cur].ch[1]) dfs(sp[cur].ch[1]);
}

int n,m;

int main(){
	scanf("%d %d", &n, &m);
	for(int i=1;i<=n;i++) a[i+1]=i;
	a[1]=-inf;a[n+2]=inf;
	len=0;
	root=built(0,1,n+2);
	sp[0].size=0;
	for(int i=1;i<=m;i++){
		int l,r;
		scanf("%d %d", &l, &r);
		flip(l+1,r+1);
	}
	dfs(root);
	return 0;
}