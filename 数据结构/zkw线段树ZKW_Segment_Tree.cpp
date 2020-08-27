#include <cstdio>
#include <cstring>
#define LL long long
#define MAXN 100005

struct node{
	LL sum,tag;
}sgt[MAXN<<2];

int M;

int a[MAXN];

void built(int n){
	for(M=1;M<n+2;M<<=1);
	memset(sgt+M,0,M*sizeof(sgt[0]));
	for(int i=1;i<=n;i++)
		sgt[M+i].sum=a[i];
	for(int i=M-1;i;i--)
		sgt[i].sum=sgt[i<<1].sum+sgt[i<<1|1].sum;
}

void modify(int l,int r,LL del){
	LL len=1,lc=0,rc=0;
	for(l=l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1,len<<=1){
		if(~l&1) sgt[l+1].tag+=del, lc+=len;
		if(r&1) sgt[r-1].tag+=del, rc+=len;
		sgt[l>>1].sum+=del*lc;
		sgt[r>>1].sum+=del*rc;
	}
	for(lc+=rc,l>>=1;l;l>>=1)
		sgt[l].sum+=del*lc;
}

LL query(int l,int r){
	LL res=0,len=1,lc=0,rc=0;
	for(l=l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1,len<<=1){
		if(~l&1) res+=sgt[l+1].sum+sgt[l+1].tag*len, lc+=len;
		if(r&1) res+=sgt[r-1].sum+sgt[r-1].tag*len, rc+=len;
		res+=sgt[l>>1].tag*lc;
		res+=sgt[r>>1].tag*rc;
	}
	for(lc+=rc,l>>=1;l;l>>=1)
		res+=sgt[l].tag*lc;
	return res;
}

int main(){
	int n,m;
	scanf("%d %d", &n, &m);
	for(int i=1;i<=n;i++)
		scanf("%d", &a[i]);
	built(n);
	for(int i=1;i<=m;i++){
		int opt,x,y;
		scanf("%d %d %d", &opt, &x, &y);
		if(opt==1){
			int k;
			scanf("%d", &k);
			modify(x,y,k);
		}
		else{
			printf("%lld\n", query(x,y));
		}
	}
	return 0;
}