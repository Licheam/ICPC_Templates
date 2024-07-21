#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAXN 10005
#define MAXM 100005

using namespace std;

const int inf = 0x3f3f3f3f;

int n,m,s,t,tot,head[MAXN],vis[MAXN];

struct edge{
    int to,cf,next;
}e[MAXM<<1];

struct node{
    int fr,edge;
}pre[MAXN];

void add(int x,int y,int z){
    tot++;
    e[tot].cf=z;
    e[tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

bool find_augment(){
    memset(pre+1,0,n*sizeof(pre[0]));
    memset(vis+1,0,n*sizeof(vis[0]));
    queue<int> q;
    vis[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int p=head[u];p;p=e[p].next){
            int v=e[p].to;
            if(!vis[v] && e[p].cf){
                pre[v].fr=u;
                pre[v].edge=p;
                vis[v]=1;
                q.push(v);
                if(v==t) return true;
            }
        }
    }
    return false;
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

int edmonds_karp(){
    int flow=0;
    while(find_augment()){
        flow+=min_flow();
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
    printf("%d\n", edmonds_karp());
    return 0;
}