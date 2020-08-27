#include <cstdio>
#define maxn 10005

int n,m,a,b,c,fa[maxn];

void ini(){
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
}

int find(int x){
	if(fa[x] == x)
		return x;
	return fa[x]=find(fa[x]);
}

void join(int x, int y){
	fa[find(x)]=find(y);
}

int main(){
	scanf("%d %d", &n, &m);
	ini();
	for(int i=1; i<=m; i++){
		scanf("%d %d %d", &a, &b, &c);
		if(a==1)
			join(b,c);
		else if(find(b)==find(c))
			puts("Y");
		else puts("N");
	}
	return 0;
}
