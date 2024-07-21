#include <cstdio>
#include <algorithm>
#define LL long long
#define MAXN 270005
#define MOD 998244353
#define RT 3

using namespace std;

LL omg[MAXN],iomg[MAXN];

LL binpow(LL x,LL y,LL mod){
	LL r=1%mod;
	while(y){
		if(y&1) r=(r*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return r;
}

void init(int n){
	omg[0]=iomg[0]=1;
	omg[1]=binpow(RT,(MOD-1)/n,MOD);
	iomg[1]=binpow(omg[1],MOD-2,MOD);
	for(int i=2;i<n;i++){
		omg[i]=omg[i-1]*omg[1]%MOD;
		iomg[i]=iomg[i-1]*iomg[1]%MOD;
	}
}

void NTT(int n,LL* P,LL* w){
	for(int i=0,j=0;i<n;i++){
		if(i<j) swap(P[i],P[j]);
		for(int l=n>>1;(j^=l)<l;l>>=1);
	}
	
	for(int i=2,l;i<=n;i<<=1){
		l=i>>1;
		for(int j=0;j<n;j+=i){
			for(int k=0;k<l;k++){
				LL t=P[j+l+k]*w[n/i*k]%MOD;
				P[j+l+k]=(P[j+k]-t+MOD)%MOD;
				P[j+k]=(P[j+k]+t)%MOD;
			}
		}
	}
}

void poly_inv(int dgr,LL* X,LL* Y){
	if(dgr==1){
		Y[0]=binpow(X[0],MOD-2,MOD);
	}
	else{
		poly_inv((dgr+1)>>1,X,Y);

		static LL Z[MAXN];
		int lim;
		for(lim=1;lim<(dgr<<1);lim<<=1);
		copy(X,X+dgr,Z);
		fill(Z+dgr,Z+lim,0);
		init(lim);

		NTT(lim,Z,omg);
		NTT(lim,Y,omg);
		for(int i=0;i<lim;i++)
			Y[i]=(2-Z[i]*Y[i]%MOD+MOD)*Y[i]%MOD;
		NTT(lim,Y,iomg);
		LL invlim=binpow(lim,MOD-2,MOD);
		for(int i=0;i<dgr;i++)
			Y[i]=Y[i]*invlim%MOD;
		fill(Y+dgr,Y+lim,0);
	}
}

int n;
LL A[MAXN],B[MAXN];

int main(){
	scanf("%d", &n);
	for(int i=0;i<n;i++)
		scanf("%lld", &A[i]);
	poly_inv(n,A,B);
	for(int i=0;i<n;i++)
		printf("%lld ", B[i]);
	return 0;
}