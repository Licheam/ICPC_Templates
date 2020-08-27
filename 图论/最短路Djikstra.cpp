#include <cstdio>
#include <cstring>
#include <climits>
#include <set>

#define LL long long
#define MAXN 100005
#define MAXM 500005

using namespace std;

struct edge{
	int v,next,to;
}e[MAXM];

int n,m,p,tot=0,dist[MAXN],head[MAXN];

void add(int x, int y, int z){
	tot++;
	e[tot].v=z;
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

struct node{
	int v,u;
	bool operator<(const node a)const{
		if(v!=a.v)
			return v<a.v;
		else
			return u<a.u;
	}
	node(int x,int y):v(x),u(y){}
};

set<node> s;//v,u
set<node>::iterator ite;
int u,q;
LL tem;

void djikstra(int x){
	for(int i=1;i<=n;i++){
		dist[i]=INT_MAX;
	}
	dist[x]=0;
	s.insert(node(0,x));
	while(!s.empty()){
		ite=s.begin();
		u=ite->u;
		s.erase(ite);
		for(int q=head[u];q;q=e[q].next){
			int v=e[q].to,w=e[q].v;
			if(dist[u]+w<dist[v]){
				ite=s.find(node(dist[v],v));
				if(ite!=s.end()) s.erase(ite);
				dist[v]=dist[u]+w;
				s.insert(node(dist[v],v));
			}
		}
	}
}

int main(){
	scanf("%d %d %d", &n, &m ,&p);
	memset(head+1,0,sizeof(head[0])*n);
	for(int i=1;i<=m;i++){
		int f,g,w;
		scanf("%d %d %d", &f, &g, &w);
		add(f,g,w);
	}
	djikstra(p);
	for(int i=1;i<=n;i++)
		printf("%d ", dist[i]);
	return 0;
}