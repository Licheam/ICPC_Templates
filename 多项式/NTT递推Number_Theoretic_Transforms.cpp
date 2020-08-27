#include <cstdio>
#include <algorithm>
#define LL long long
#define MAXN 2100005
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

int n,m,lim;
LL A[MAXN],B[MAXN];

int main(){
	scanf("%d %d", &n, &m);
	for(lim=1;lim<=n+m;lim<<=1);
	for(int i=0;i<n+1;i++){
		scanf("%lld", &A[i]);
	}
	for(int i=0;i<m+1;i++){
		scanf("%lld", &B[i]);
	}
	init(lim);
	NTT(lim,A,omg);
	NTT(lim,B,omg);
	for(int i=0;i<lim;i++)
		A[i]=A[i]*B[i]%MOD;
	NTT(lim,A,iomg);
	LL invn=binpow(lim,MOD-2,MOD);
	for(int i=0;i<n+m+1;i++)
		printf("%lld ", A[i]*invn%MOD);
	return 0;
}