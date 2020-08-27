#include <cstdio>
#include <cstring>
#define LL long long
#define MAXN 105
#define MOD 1000000007

LL n,k;

struct Matrix{
	LL num[MAXN][MAXN];

	Matrix(int opt){
		memset(num,0,sizeof(num));
		if(opt==1)
			for(int i=1;i<=n;i++)
				num[i][i]=1;
	}

	Matrix operator*(const Matrix y){
		Matrix x=*this,ans(0);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				for(int k=1;k<=n;k++){
					ans.num[i][j]=(ans.num[i][j]+x.num[i][k]*y.num[k][j]%MOD)%MOD;
				}
			}
		}
		return ans;
	}
};

Matrix binpow(Matrix x,LL y){
	Matrix r(1);
	while(y){
		if(y&1) r=r*x;
		x=x*x;
		y>>=1;
	}
	return r;
}

int main(){
	scanf("%lld %lld", &n, &k);
	Matrix A(0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%lld", &A.num[i][j]);
		}
	}
	A=binpow(A,k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%lld ", A.num[i][j]);
		}
		puts("");
	}
	return 0;
}