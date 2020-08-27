#include <cstdio>

#define _for(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
#define MAXN 1005

int n,m,H,p,q,bit[MAXN][MAXN];

int lowbit(int x){
	return x&(-x);
}

void change(int x,int y,int k){
	for(int i=x;i<=n;i+=lowbit(i)){
		for(int j=y;j<=m;j+=lowbit(j)){
			bit[i][j]+=k;
		}
	}
}

int sum(int x,int y){
	int s=0;
	for(int i=x;i>0;i-=lowbit(i)){
		for(int j=y;j>0;j-=lowbit(j)){
			s+=bit[i][j];
		}
	}
	return s;
}

int main(){
	scanf("%d %d %d",&n, &m, &H);
	_for(i,1,n+1)
		_for(j,1,m+1)
			bit[i][j]=0;
	_for(i,1,H){
		scanf("%d %d", &p, &q);
		change(1,1,1);
		change(p+1,1,-1);
		change(1,q+1,-1);
		change(p+1,q+1,1);//1-2+1
	}
	_for(i,1,n)
		_for(j,1,m)
			printf("%d\n", sum(i,j));
}