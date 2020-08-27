#include <cstdio>
#include <cstring>
#include <queue>
#define MAXN 2005
#define MAXM 1000005

using namespace std;

const int inf=0x3f3f3f3f;

struct edge{
    int to,cf,next;
}e[MAXM<<1];

int n,n1,n2,m,s,t;
int tot,head[MAXN],cur[MAXN],lbl[MAXN];

void add(int x,int y,int z){
    tot++;
    e[tot].to=y;
    e[tot].cf=z;
    e[tot].next=head[x];
    head[x]=tot;
}

bool bfs(){
    memset(lbl+1,0,n*sizeof(lbl[0]));
    lbl[t]=1;
    queue<int> q;
    q.push(t);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int p=head[u];p;p=e[p].next){
            int v=e[p].to;
            if(e[p^1].cf && !lbl[v]){
                lbl[v]=lbl[u]+1;
                q.push(v);
                if(v==s) return true;
            }
        }
    }
    return lbl[s]!=0;
}

int dfs(int u,int lim){
    if(u==t)return lim;

    int used=0;
    for(int& p=cur[u];p;p=e[p].next){
        int v=e[p].to;
        if(e[p].cf && lbl[v]==lbl[u]-1){
            int rest=dfs(v,min(lim-used,e[p].cf));
            used+=rest;
            e[p].cf-=rest;
            e[p^1].cf+=rest;
            if(used==lim) break;
        }
    }
    return used;
}

int dinic(){
    int flow=0;
    while(bfs()){
        for(int i=1;i<=n;i++)
            cur[i]=head[i];
        flow+=dfs(s,inf);
    }
    return flow;
}

int main(){
    scanf("%d %d %d", &n1, &n2, &m);
    n=n1+n2+2;//n个点
    s=n-1;t=n;
    tot=1;
    memset(head+1,0,n*sizeof(head[0]));
    for(int i=1;i<=m;i++){
        int f,g;
        scanf("%d %d",&f,&g);
        if(f>n1 || g>n2) continue;
        add(f,n1+g,1);
        add(n1+g,f,0);
    }
    for(int i=1;i<=n1;i++){
        add(s,i,1);
        add(i,s,0);
    }
    for(int i=n1+1;i<=n1+n2;i++){
        add(i,t,1);
        add(t,i,0);
    }
    printf("%d\n", dinic());
    return 0;
}