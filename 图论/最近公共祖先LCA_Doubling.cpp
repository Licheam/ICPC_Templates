#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 500005
#define MAXM 500005
#define MAXLN 25
using namespace std;

struct edge{
	int to,next;
}e[MAXM<<1];

int tot,head[MAXN];

void add(int x,int y){
	tot++;
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

int dep[MAXN],st[MAXN][MAXLN];

void dfs(int cur,int fa){
	dep[cur]=dep[fa]+1;
	st[cur][0]=fa;
	for(int l=1;(1<<l)<=dep[cur];l++)
		st[cur][l]=st[st[cur][l-1]][l-1];

	for(int p=head[cur];p;p=e[p].next){
		if(e[p].to==fa) continue;
		dfs(e[p].to,cur);
	}
}

int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=0;dep[x]-dep[y];i++)
		if((dep[x]-dep[y])&(1<<i)) x=st[x][i];
	if(x==y) return x;
	
	int l;
	for(l=1;(1<<l)<=dep[x];l++);
	for(int i=l;i>=0;i--)
		if(st[x][i]!=st[y][i])
			x=st[x][i], y=st[y][i];
	return st[x][0];
}

int n,m,s;

int main(){
	scanf("%d %d %d", &n, &m, &s);
	tot=0;
	memset(head+1,0,n*sizeof(head[0]));
	for(int i=1;i<n;i++){
		int f,g;
		scanf("%d %d", &f, &g);
		add(f,g);
		add(g,f);
	}
	dep[0]=0;
	dfs(s,0);
	for(int i=1;i<=m;i++){
		int f,g;
		scanf("%d %d", &f, &g);
		printf("%d\n", lca(f,g));
	}
	return 0;
}