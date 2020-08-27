#include <cstdio>
#include <algorithm>
#define MAXN 100005

using namespace std;

int n,m;

struct node{
	int rt,lc,rc,dis,v;
}lt[MAXN];

int find(int x){
	if(lt[x].rt==x)
		return x;
	return lt[x].rt=find(lt[x].rt);
}

int merge(int x,int y){
	if(!x || !y) return x+y;
	if(lt[x].v>lt[y].v || (lt[x].v==lt[y].v && x>y)) swap(x,y);//后一个条件蜜汁优化？
	lt[x].rc=merge(lt[x].rc,y);
	lt[lt[x].rc].rt=x;
	if(lt[lt[x].lc].dis<lt[lt[x].rc].dis) swap(lt[x].lc,lt[x].rc);
	lt[x].dis=lt[lt[x].rc].dis+1;
	return x;
}

void pop(int x){
	lt[x].v=-1;
	lt[lt[x].lc].rt=lt[x].lc;
	lt[lt[x].rc].rt=lt[x].rc;
	lt[x].rt=merge(lt[x].lc,lt[x].rc);
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i=1;i<=n;i++){
		scanf("%d", &lt[i].v);
		lt[i].rt=i;
		lt[i].lc=lt[i].rc=0;
		lt[i].dis=0;
	}
	lt[0].dis=0;
	for(int i=1;i<=m;i++){
		int opt;
		scanf("%d",&opt);
		if(opt==1){
			int x,y;
			scanf("%d %d", &x, &y);
			int rx=find(x),ry=find(y);
			if(lt[x].v==-1||lt[y].v==-1||rx==ry)
				continue;
			merge(rx,ry);
		}
		else{
			int x;
			scanf("%d", &x);
			if(lt[x].v==-1)
				printf("-1\n");
			else{
				int rx=find(x);
				printf("%d\n", lt[rx].v);
				pop(rx);
			}
		}
	}
	return 0;
}