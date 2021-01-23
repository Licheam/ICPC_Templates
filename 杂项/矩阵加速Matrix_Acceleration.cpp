#include <cstdio>
#include <cstring>
#define LL long long
#define MAXN 5
#define MOD 1000000007

struct Matrix{
	int num[MAXN][MAXN];
	int n,m;

	Matrix(int nn,int mm){
		n=nn; m=mm;
		memset(num,0,sizeof(num));
	}
	Matrix(int nn){
		n=m=nn;
		memset(num,0,sizeof(num));
		for(int i=1;i<=nn;i++) num[i][i]=1;
	}

	Matrix operator*(const Matrix y){
		Matrix x=*this,ans(x.n,y.m);
		if(x.m!=y.n) return ans;
		for(int i=1;i<=x.n;i++){
			for(int j=1;j<=y.m;j++){
				for(int k=1;k<=x.m;k++){
					ans.num[i][j]=(ans.num[i][j]+1LL*x.num[i][k]*y.num[k][j]%MOD)%MOD;
				}
			}
		}
		return ans;
	}
};

Matrix binpow(Matrix x,LL y){
	Matrix r(x.n);
	while(y){
		if(y&1) r=r*x;
		x=x*x;
		y>>=1;
	}
	return r;
}

int main(){
	int T;
	scanf("%d", &T);
	while(T--){
		int n;
		scanf("%d", &n);
		if(n<=3) printf("1\n");
		else{
			Matrix x(3,3);
			x.num[1][1]=x.num[2][1]=x.num[1][3]=x.num[3][2]=1;
			x=binpow(x,n-3);
			Matrix y(3,1);
			for(int i=1;i<=3;i++) y.num[i][1]=1;
			printf("%d\n", (x*y).num[1][1]);
		}
	}
	return 0;
}