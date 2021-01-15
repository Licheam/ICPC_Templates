#include <cstdio>
#include <algorithm>
using namespace std;
#define LL long long
const int MAXN=2100005
const int MOD=998244353
const int RT=3;

LL binpow(LL x,LL y,LL mod){
	LL r=1%mod;
	while(y){
		if(y&1) r=(r*x)%mod;
		x=(x*x)%mod;
		y>>=1;
	}
	return r;
}

void NTT(int n,int* P,int f){
	for(int i=0,j=0;i<n;i++){
		if(i<j) swap(P[i],P[j]);
		for(int l=n>>1;(j^=l)<l;l>>=1);
	}
	
	for(int i=2,l;i<=n;i<<=1){
		l=i>>1;
		int wn=binpow(RT,(MOD-1)/i,MOD);
		if(f==-1) wn=binpow(wn,MOD-2,MOD);
		for(int j=0;j<n;j+=i){
			int w=1;
			for(int k=0;k<l;k++,w=1LL*w*wn%MOD){
				int t=1LL*P[j+l+k]*w%MOD;
				P[j+l+k]=1LL*(P[j+k]-t+MOD)%MOD;
				P[j+k]=1LL*(P[j+k]+t)%MOD;
			}
		}
	}
}

int A[MAXN],B[MAXN];

int main(){
	int n,m;
	scanf("%d %d", &n, &m);
	int lim;
	for(lim=1;lim<=n+m;lim<<=1);
	for(int i=0;i<n+1;i++){
		scanf("%d", &A[i]);
	}
	for(int i=0;i<m+1;i++){
		scanf("%d", &B[i]);
	}
	NTT(lim,A,1);
	NTT(lim,B,1);
	for(int i=0;i<lim;i++)
		A[i]=1LL*A[i]*B[i]%MOD;
	NTT(lim,A,-1);
	int invn=binpow(lim,MOD-2,MOD);
	for(int i=0;i<n+m+1;i++)
		printf("%lld ", 1LL*A[i]*invn%MOD);
	return 0;
}