#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAXN 5005
#define MAXM 50005

const int inf = 0x3f3f3f3f;

using namespace std;

int n,m,s,t,tot,head[MAXN],dis[MAXN],maxflow,mincost;
bool inque[MAXN];

struct edge{//残量网络 residual network
    int to,cf,next,dis;//Cf:residual capacity
}e[(MAXM<<1)+1];

struct node{
    int fr,edge;
}pre[MAXN];

void add(int x,int y,int f,int d){
    tot++;
    e[tot].cf=f;
    e[tot].dis=d;
    e[tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

bool spfa(){//SPFA
    memset(dis+1,inf,n*sizeof(dis[0]));
    memset(inque+1,0,n*sizeof(inque[0]));
    pre[t].fr=0;
    queue<int> q;
    dis[s]=0;
    q.push(s);
    inque[s]=1;
    while(!q.empty()){
        int u=q.front();q.pop();
        inque[u]=0;
        for(int p=head[u];p;p=e[p].next){
            int v=e[p].to;
            if(e[p].cf && dis[v]>dis[u]+e[p].dis){
                dis[v]=dis[u]+e[p].dis;
                pre[v].fr=u;
                pre[v].edge=p;
                if(!inque[v]){
                    q.push(v);
                    inque[v]=1;
                }
            }
        }
    }
    return pre[t].fr!=0;
}

int min_flow(){
    int mn=inf;
    for(int u=t;u!=s;u=pre[u].fr){
        mn=min(mn,e[pre[u].edge].cf);
    }
    for(int u=t;u!=s;u=pre[u].fr){
        e[pre[u].edge].cf-=mn;
        e[pre[u].edge^1].cf+=mn;
    }
    return mn;
}

void edmonds_karp(){
    maxflow=0,mincost=0;
    while(spfa()){
        int flow=min_flow();
        maxflow+=flow;
        mincost+=flow*dis[t];
    }
}

int main(){
    scanf("%d %d %d %d", &n, &m, &s, &t);
    tot=1;
    memset(head+1,0,n*sizeof(head[0]));
    for(int i=1;i<=m;i++){
        int f,g,w,d;
        scanf("%d %d %d %d",&f,&g,&w,&d);
        add(f,g,w,d);
        add(g,f,0,-d);
    }
    edmonds_karp();
    printf("%d %d\n",maxflow,mincost);
    return 0;
}