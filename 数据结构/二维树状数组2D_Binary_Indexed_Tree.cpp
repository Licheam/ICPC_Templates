#include <bits/stdc++.h>
const int MAXN=2005;

struct BIT {
	int n,m;
	int a[MAXN][MAXN];

	int lowbit(int x){
		return x&(-x);
	}

	void change(int x,int y,int k){
		for(int i=x;i<=n;i+=lowbit(i)){
			for(int j=y;j<=m;j+=lowbit(j)){
				a[i][j]+=k;
			}
		}
	}

	int sum(int x,int y){
		int s=0;
		for(int i=x;i>0;i-=lowbit(i)){
			for(int j=y;j>0;j-=lowbit(j)){
				s+=a[i][j];
			}
		}
		return s;
	}
}bit;

int main(){
	int n,m,H;
	scanf("%d %d %d",&n, &m, &H);
	bit.n=n;
	bit.m=m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			bit.a[i][j]=0;
	for(int i=1;i<=H;i++) {
		int x,y;
		scanf("%d %d", &x, &y);
		bit.change(1,1,1);
		bit.change(x+1,1,-1);
		bit.change(1,y+1,-1);
		bit.change(x+1,y+1,1);//1-2+1
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			printf("%d\n", bit.sum(i,j));
}