#include <cstdio>
#define LL long long
#define MAXN 100005
#define MAXT 400005

int n,m,p,a[MAXN];

struct node{
	int le,ri;
	LL sum,del,mul;
}sgt[MAXT];

void built(int cur,int l,int r){
	sgt[cur].le=l; sgt[cur].ri=r;
	sgt[cur].del=0; sgt[cur].mul=1;
	if(l<r-1){
		built(cur<<1,l,(l+r)>>1);
		built(cur<<1|1,(l+r)>>1,r);
		sgt[cur].sum=sgt[cur<<1].sum+sgt[cur<<1|1].sum;
	}
	else sgt[cur].sum=a[l];
}

void update(int cur){
	int lc=cur<<1,rc=lc|1;
	sgt[lc].sum=(sgt[lc].sum*sgt[cur].mul+sgt[cur].del*(sgt[lc].ri-sgt[lc].le))%p;
	sgt[rc].sum=(sgt[rc].sum*sgt[cur].mul+sgt[cur].del*(sgt[rc].ri-sgt[rc].le))%p;
	sgt[lc].mul=sgt[lc].mul*sgt[cur].mul%p;
	sgt[rc].mul=sgt[rc].mul*sgt[cur].mul%p;
	sgt[lc].del=(sgt[lc].del*sgt[cur].mul+sgt[cur].del)%p;
	sgt[rc].del=(sgt[rc].del*sgt[cur].mul+sgt[cur].del)%p;
	sgt[cur].mul=1; sgt[cur].del=0;
}

void plus(int cur,int l,int r,LL del){
	if(l<=sgt[cur].le && sgt[cur].ri<=r){
		sgt[cur].sum=(sgt[cur].sum+del*(sgt[cur].ri-sgt[cur].le))%p;
		sgt[cur].del=(sgt[cur].del+del)%p;
	}
	else{
		int lc=cur<<1,rc=lc|1,mid=(sgt[cur].le+sgt[cur].ri)>>1;
		update(cur);
		if(l<mid)
			plus(lc,l,r,del);
		if(r>mid)
			plus(rc,l,r,del);
		sgt[cur].sum=sgt[lc].sum+sgt[rc].sum;
	}
}

void multi(int cur,int l,int r,LL mul){
	if(l<=sgt[cur].le && sgt[cur].ri<=r){
		sgt[cur].sum=(sgt[cur].sum*mul)%p;
		sgt[cur].del=(sgt[cur].del*mul)%p;
		sgt[cur].mul=(sgt[cur].mul*mul)%p;
	}
	else{
		int lc=cur<<1,rc=lc|1,mid=(sgt[cur].le+sgt[cur].ri)>>1;
		update(cur);
		if(l<mid)
			multi(lc,l,r,mul);
		if(r>mid)
			multi(rc,l,r,mul);
		sgt[cur].sum=sgt[lc].sum+sgt[rc].sum;
	}
}

LL query(int cur,int l,int r){
	if(l<=sgt[cur].le && sgt[cur].ri<=r){
		return sgt[cur].sum;
	}
	else{
		int lc=cur<<1,rc=lc|1,mid=(sgt[cur].le+sgt[cur].ri)>>1;
		update(cur);
		LL sum=0;
		if(l<mid)
			sum=(sum+query(lc,l,r))%p;
		if(r>mid)
			sum=(sum+query(rc,l,r))%p;
		return sum;
	}
}

int main(){
	scanf("%d %d %d",&n,&m,&p);
	for(int i=1;i<=n;i++)
		scanf("%d", &a[i]);
	built(1,1,n+1);
	while(m--){
		int opt,l,r;
		LL k;
		scanf("%d", &opt);
		if(opt==1){
			scanf("%d %d %lld", &l, &r, &k);
			multi(1,l,r+1,k);
		}
		else if(opt==2){
			scanf("%d %d %lld", &l, &r, &k);
			plus(1,l,r+1,k);
		}
		else{
			scanf("%d %d", &l, &r);
			printf("%lld\n", query(1,l,r+1));
		}

	}
	return 0;
}