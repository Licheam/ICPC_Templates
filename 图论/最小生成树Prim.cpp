#include <cstdio>
#include <cstdlib>
#include <queue>

#define MAXN 5005
#define MAXM 200005

using namespace std;

struct edge
{
	int v,to,next;
}e[MAXM<<1];

int n,m,f,g,w,tot=0,head[MAXN],ans=0,flag[MAXN];

void add(int x, int y, int z){
	e[++tot].v=z;
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

struct HeapNode
{
	int v,u;
	bool operator <(const HeapNode& a) const{
		return v > a.v;
	}
};

priority_queue<HeapNode> Q;

void prim(){
	for(int i=1;i<=n;i++)
		flag[i]=0;
	flag[1]=1;
	for(int p=head[1];p;p=e[p].next)
		Q.push((HeapNode){e[p].v,e[p].to});
	for(int i=1,u;i<n;i++){
		while(flag[Q.top().u]){
			Q.pop();
			if(Q.empty()){
				puts("orz");
				exit(0);
			}
		}
		ans+=Q.top().v;
		u=Q.top().u;
		Q.pop();
		flag[u]=1;
		for(int p=head[u];p;p=e[p].next)
			if(!flag[e[p].to])
				Q.push((HeapNode){e[p].v,e[p].to});
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i=1;i<=n;i++)
		head[i]=0;
	for(int i=1;i<=m;i++){
		scanf("%d %d %d",&f,&g,&w);
		add(f,g,w);
		add(g,f,w);
	}
	prim();
	printf("%d",ans);
	return 0;
}