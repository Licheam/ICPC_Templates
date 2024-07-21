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

int n,m,tot,head[MAXN];
int dist[MAXN],cnt[MAXN];
bool flag[MAXN];

void add(int x,int y,int z){
	tot++;
	e[tot].v=z;
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

bool spfa(int x){//负环return false
	queue <int> Q;
	memset(dist+1,inf,n*sizeof(dist[0]));
	memset(flag+1,0,n*sizeof(flag[0]));
	memset(cnt+1,0,n*sizeof(cnt[0]));

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
				if(!flag[v]) {
					Q.push(v);
					flag[v]=true;
					if(++cnt[v]>=n){
						return false;
					}
				}
			}
		}
	}
	return true;
}

void solve() {
	scanf("%d %d",&n,&m);
	tot=0;
	memset(head+1,0,n*sizeof(head[0]));
	for(int i=1;i<=m;i++){
		int f,g,w;
		scanf("%d %d %d", &f, &g, &w);
		add(f,g,w);
		if(w>=0) add(g,f,w);
	}
	if(spfa(1)) printf("NO\n");
	else printf("YES\n");
}

int main(){
	int T=1;
	scanf("%d", &T);
	while(T--) {
		solve();
	}
	return 0;
}