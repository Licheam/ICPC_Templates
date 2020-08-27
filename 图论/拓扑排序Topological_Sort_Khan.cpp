#include <cstdio>
#include <cstring>
#include <stack>
#define MAXN 100005
#define MAXM 200005

using namespace std;

struct edge{
    int to,next;
}e[MAXM];

int n,m,tot,head[MAXN],indgr[MAXN],list[MAXN];
bool flag[MAXN];

void add(int x,int y){
    tot++;
    e[tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

void khan(){
    stack<int> s;
    int cnt=0;
    memset(flag+1,0,n*sizeof(flag[0]));
    for(int i=1;i<=n;i++){
        if(!flag[i] && indgr[i]==0){
            s.push(i);
            flag[i]=true;
            while(!s.empty()){
                int u=s.top();s.pop();
                list[++cnt]=u;
                flag[u]=true;
                for(int p=head[u];p;p=e[p].next){
                    int v=e[p].to;
                    indgr[v]--;
                    if(indgr[v]==0)
                        s.push(v);
                }
            }
        }
    }
}

int main(){
    scanf("%d %d",&n,&m);
    memset(head+1,0,n*sizeof(head[0]));
    memset(indgr+1,0,n*sizeof(indgr[0]));
    tot=0;
    for(int i=1;i<=m;i++){
        int f,g;
        scanf("%d %d", &f, &g);
        add(f,g);
        indgr[g]++;
    }
    khan();
    for(int i=1;i<=n;i++)
        printf("%d ", list[i]);
    return 0;
}