#include <cstdio>
#include <cstring>
#include <queue>
#define MAXN 2005
#define MAXM 1000005

const int inf=0x3f3f3f3f;

using namespace std;

int n1,n2,n,m,tot,head[MAXN];
int mat[MAXN],lb[MAXN],dfn[MAXN];

struct edge{
    int to,next;
}e[MAXM];

void add(int x,int y){
    tot++;
    e[tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

bool bfs(){
    memset(lb+1,0,n*sizeof(lb[0]));
    queue<int> q;
    for(int i=1;i<=n1;i++){
        if(!mat[i]){
            q.push(i);
            lb[i]=1;
        }
    }
    int dis=inf;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int p=head[u];p;p=e[p].next){
            int v=e[p].to;
            if(!lb[v]){
                lb[v]=lb[u]+1;
                if(!mat[v]) dis=lb[v];
                else if(lb[v]<dis){
                    lb[mat[v]]=lb[v]+1;
                    q.push(mat[v]);
                }
            }
        }
    }
    return dis!=inf;
}

bool dfs(int u,int stamp){
    for(int p=head[u];p;p=e[p].next){
        int v=e[p].to;
        if(dfn[v]!=stamp && lb[v]==lb[u]+1){
            dfn[v]=stamp;
            if(!mat[v] || (lb[mat[v]]==lb[v]+1 && dfs(mat[v],stamp))){
                mat[v]=u;
                mat[u]=v;
                return true;
            }
        }
    }
    return false;
}

int hopcroft_karp(){
    int cnt=0,stamp=0;
    memset(dfn+1,0,n*sizeof(dfn[0]));
    memset(mat+1,0,n*sizeof(mat[0]));
    while(bfs()){
        stamp++;
        for(int i=1;i<=n1;i++){
            if(!mat[i] && dfs(i,stamp)){
                cnt++;
            }
        }
    }
    return cnt;
}

int main(){
    scanf("%d %d %d", &n1, &n2, &m);
    n=n1+n2;
    memset(head+1,0,n*sizeof(head[0]));
    tot=0;
    for(int i=1;i<=m;i++){
        int f,g;
        scanf("%d %d",&f,&g);
        if(f>n1 || g>n2) continue;
        add(f,n1+g);
    }
    printf("%d\n", hopcroft_karp());
    return 0;
}