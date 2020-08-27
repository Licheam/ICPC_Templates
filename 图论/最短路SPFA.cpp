#include <cstdio>
#include <cstring>
#include <queue>

#define MAXN 100005
#define MAXM 500005
const int inf=0x3f3f3f3f;

using namespace std;

struct edge{
	int v,to,next;
}e[MAXM];

int n,m,p,tot,head[MAXN],dist[MAXN];
bool flag[MAXN];

void add(int x,int y,int z){
	tot++;
	e[tot].v=z;
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

void spfa(int x){
	queue <int> Q;
	memset(dist+1,inf,n*sizeof(dist[0]));
	memset(flag+1,0,n*sizeof(flag[0]));

	Q.push(x);
	flag[x]=true;
	dist[x]=0;
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		flag[u]=false;
		for(int q=head[u];q;q=e[q].next){
			int v=e[q].to;
			if(dist[u]+e[q].v<dist[v]){
				dist[v]=dist[u]+e[q].v;
				if(!flag[v]){
					Q.push(v);
					flag[v]=true;
				}
			}
		}
	}
}

int main(){
	scanf("%d %d %d",&n,&m,&p);
	tot=0;
	memset(head+1,0,n*sizeof(head[0]));
	for(int i=1;i<=m;i++){
		int f,g,w;
		scanf("%d %d %d", &f, &g, &w);
		add(f,g,w);
	}
	spfa(p);
	for(int i=1;i<=n;i++)
		printf("%d ", dist[i]==inf?2147483647:dist[i]);
	return 0;
}