#include <cstdio>
#define MAXN 500005
#define MAXM 500005

struct edge{
	int to,next;
}e[MAXM<<1],eq[MAXM<<1];

int n,m,s,tot,totq,head[MAXN],headq[MAXN],fa[MAXN],ans[MAXM];

void add(int x, int y){
	tot++;
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

void addq(int x, int y){
	tot++;
	eq[tot].to=y;
	eq[tot].next=headq[x];
	headq[x]=tot;
}

int find(int x){
	if(fa[x]==x)
		return x;
	return fa[x]=find(fa[x]);
}

void tarjan(int x){
	fa[x]=x;
	for(int p=head[x];p;p=e[p].next){
		int u=e[p].to;
		if(!fa[u]){
			tarjan(u);
			fa[u]=x;
		}
	}
	for(int p=headq[x];p;p=eq[p].next){
		int u=eq[p].to;
		if(fa[u]){
			ans[(p+1)>>1]=find(u);
		}
	}
}

int main(){
	scanf("%d %d %d", &n, &m, &s);
	for(int i=1;i<=n;i++){
		head[i]=0;
		headq[i]=0;
	}
	tot=0;
	for(int i=1;i<n;i++){
		int f,g;
		scanf("%d %d",&f,&g);
		add(f,g);
		add(g,f);
	}
	tot=0;
	for(int i=1;i<=m;i++){
		int f,g;
		scanf("%d %d",&f,&g);
		addq(f,g);
		addq(g,f);
	}
	for(int i=1;i<=n;i++){
		fa[i]=0;
	}
	tarjan(s);
	for(int i=1;i<=m;i++)
		printf("%d\n", ans[i]);
	return 0;
}