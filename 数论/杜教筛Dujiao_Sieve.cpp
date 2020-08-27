#include <cstdio>
#include <cstring>
#define LL long long
#define MAXR R+5
#define R 2000000//r=n^(2/3)

int n,r,p[MAXR],cnt;
bool inp[MAXR];

LL phi[MAXR],sphi[MAXR],sphir[MAXR],mu[MAXR],smu[MAXR],smur[MAXR];

void pre(){
	memset(inp+1,0,r*sizeof(inp[0]));
	inp[0]=inp[1]=1;
	cnt=0;
	sphi[1]=phi[1]=1;
	smu[1]=mu[1]=1;
	for(int i=2;i<=r;i++){
		if(!inp[i]) p[++cnt]=i, phi[i]=i-1, mu[i]=-1;
		for(int j=1;j<=cnt&&i*p[j]<=r;j++){
			inp[i*p[j]]=1;
			if(i%p[j]){
				phi[i*p[j]]=phi[i]*(p[j]-1);
				mu[i*p[j]]=-mu[i];
			}
			else{
				phi[i*p[j]]=phi[i]*p[j];
				mu[i*p[j]]=0;
				break;
			}
		}
		sphi[i]=sphi[i-1]+phi[i];
		smu[i]=smu[i-1]+mu[i];
	}
}

LL sumphi(LL x){
	if(x<=r) return sphi[x];
	else if(sphir[n/x]) return sphir[n/x];
	LL &sx=sphir[n/x];
	sx=x*(x+1)/2;
	for(LL i=2;i<=x;i++){
		LL t=x/i,j=x/t;
		sx-=(j-i+1)*sumphi(t);
		i=j;
	}
	return sx;
}

LL summu(LL x){
	if(x<=r) return smu[x];
	else if(smur[n/x]) return smur[n/x];
	LL &sx=smur[n/x];
	sx=1;
	for(LL i=2;i<=x;i++){
		LL t=x/i,j=x/t;
		sx-=(j-i+1)*summu(t);
		i=j;
	}
	return sx;
}

int main(){
	int T;
	scanf("%d", &T);
	r=R;
	pre();
	while(T--){
		scanf("%d", &n);
		memset(sphir+1,0,(n/r)*sizeof(sphir[0]));
		memset(smur+1,0,(n/r)*sizeof(smur[0]));
		printf("%lld %lld\n", sumphi(n), summu(n));
	}
	return 0;
}