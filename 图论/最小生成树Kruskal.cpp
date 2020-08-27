#include <cstdio>
#include <algorithm>

#define MAXN 5005
#define MAXM 200005
#define _for(i,a,b) for(int i=(a);i<=(b);i++)

using namespace std;

int read(){
	int ng=0,x=0;
	char ch=getchar();
	for(;ch<'0' || ch>'9';ch=getchar()) ng|=ch=='-';
	for(;ch>='0' && ch<='9';ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return ng?-x:x;
}

struct road
{
	int f,g,w;
}r[MAXM];

struct cmpf
{
	bool operator() (const road& a, const road& b) const {
		return a.w<b.w;
	}
};

int n,m,ans=0,fa[MAXN];

int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

void kruskal(){
	int rx,ry;

	sort(r+1, r+m+1, cmpf());
	_for(i,1,m){
		rx=find(r[i].f);
		ry=find(r[i].g);
		if(rx==ry)
			continue;
		fa[rx]=ry;
		ans+=r[i].w;
	}
}

int main(){
	n=read();m=read();
	_for(i,1,m){
		r[i].f=read();
		r[i].g=read();
		r[i].w=read();
	}
	_for(i,1,n)
		fa[i]=i;
	kruskal();
	_for(i,2,n){
		if(find(i)!=find(i-1)){
			puts("orz");
			return 0;
		}
	}
	printf("%d", ans);
}