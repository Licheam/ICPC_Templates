#include <cstdio>
#include <cstring>
#define MAXN 1005
#define MAXM 1000005

struct node{
	int to,next;
}e[MAXM];

int n1,n2,m,head[MAXN],tot,dfn[MAXN],mat[MAXN];

void add(int x,int y){
	tot++;
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

bool augment(int x,int stamp){
	for(int p=head[x];p;p=e[p].next){
		int u=e[p].to;
		if(dfn[u] == stamp) continue;
		dfn[u]=stamp;
		if(!mat[u] || augment(mat[u],stamp)){
			mat[u]=x;
			return true;
		}
	}
	return false;
}

int match(){
	memset(mat+1,0,n2*sizeof(mat[0]));
	memset(dfn+1,0,n2*sizeof(dfn[0]));
	int cnt=0;
	for(int i=1;i<=n1;i++){
		if(augment(i,i))
			cnt++;
	}
	return cnt;
}

int main(){
	scanf("%d %d %d", &n1,&n2,&m);
	tot=0;
	memset(head+1,0,n1*sizeof(head[0]));
	for(int i=1;i<=m;i++){
		int f,g;
		scanf("%d %d", &f, &g);
		if(f>n1 || g>n2)
			continue;
		add(f,g);
	}
	printf("%d\n", match());
	return 0;
}