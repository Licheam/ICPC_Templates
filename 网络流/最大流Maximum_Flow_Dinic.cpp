#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAXN 10005
#define MAXM 100005

const int inf = 0x3f3f3f3f;

using namespace std;

int n,m,s,t,tot,head[MAXN],lb[MAXN],cur[MAXN];

struct edge{//残量网络 residual network
    int to,cf,next;//Cf:residual capacity
}e[(MAXM<<1)+1];

void add(int x,int y,int z){
    tot++;
    e[tot].cf=z;
    e[tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

bool label_vertex(){//BFS
    memset(lb+1,0,n*sizeof(lb[0]));
    queue<int> q;
    lb[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int p=head[u];p;p=e[p].next){
            int v=e[p].to;
            if(e[p].cf && !lb[v]){
                lb[v]=lb[u]+1;
                q.push(v);
                if(v==t) return true;
            }
        }
    }
    return false;
}

int multi_augment(int u,int lim){//DFS 多路增广
    if(u == t) return lim;
    
    int used=0;
    for(int& p=cur[u];p;p=e[p].next){
        int v=e[p].to;
        if(e[p].cf && lb[v]==lb[u]+1){
            int rest=multi_augment(v,min(lim-used,e[p].cf));
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
    while(label_vertex()){//BFS 标记
        for(int i=1;i<=n;i++) cur[i]=head[i];//当前弧优化
        flow+=multi_augment(s,inf);//DFS 顺着标记找增广路
    }
    return flow;
}

int main(){
    scanf("%d %d %d %d", &n, &m, &s, &t);
    tot=1;
    memset(head+1,0,n*sizeof(head[0]));
    for(int i=1;i<=m;i++){
        int f,g,w;
        scanf("%d %d %d",&f,&g,&w);
        add(f,g,w);
        add(g,f,0);
    }
    printf("%d\n", dinic());
    return 0;
}