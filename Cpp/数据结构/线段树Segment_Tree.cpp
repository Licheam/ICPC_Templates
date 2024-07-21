#include <cstdio>
#include <algorithm>
#define LL long long
#define MAXN 100005
using namespace std;

struct SGT{
	LL sum[MAXN<<2],tag[MAXN<<2];

	void pushup(int x) {sum[x]=sum[x<<1]+sum[x<<1|1];}
	void pushdown(int x,int l,int r) {
		int m=(l+r)>>1;
		sum[x<<1]+=tag[x]*(m-l+1);
		tag[x<<1]+=tag[x];
		sum[x<<1|1]+=tag[x]*(r-m);
		tag[x<<1|1]+=tag[x];
		tag[x]=0;
	}

	void build(int x,int l,int r,LL *a) {
		tag[x]=0;
		if(l==r) sum[x]=a[l];
		else {
			int m=(l+r)>>1;
			build(x<<1,l,m,a);
			build(x<<1|1,m+1,r,a);
			pushup(x);
		}
	}

	void modify(int x,int l,int r,int ql,int qr,LL delta) {
		if(ql<=l && r<=qr) {
			sum[x]+=delta*(r-l+1);
			tag[x]+=delta;
			return;
		}
		if(tag[x]) pushdown(x,l,r);
		int m=(l+r)>>1;
		if(ql<=m) modify(x<<1,l,m,ql,qr,delta);
		if(m<qr) modify(x<<1|1,m+1,r,ql,qr,delta);
		// sum[x]=tag[x]*(r-l+1)+sum[x<<1]+sum[x<<1|1];
		pushup(x);
	}

	LL query(int x,int l,int r,int ql,int qr){
		if(ql<=l && r<=qr) return sum[x];

		if(tag[x]) pushdown(x,l,r);
		int m=(l+r)>>1;		
		LL res=0;
		if(ql<=m) res+=query(x<<1,l,m,ql,qr);
		if(m<qr) res+=query(x<<1|1,m+1,r,ql,qr);
		// res+=tag[x]*(min(qr,r)-max(ql,l)+1);
		return res;
	}
}sgt;

LL a[MAXN];

int main(){
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld", &a[i]);
	sgt.build(1,1,n,a);
	for(int i=1;i<=m;i++){
		int op,l,r;
		scanf("%d", &op);
		if(op==1){
			LL k;
			scanf("%d %d %lld",&l,&r,&k);
			sgt.modify(1,1,n,l,r,k);
		}
		else{
			scanf("%d %d",&l,&r);
			printf("%lld\n", sgt.query(1,1,n,l,r));
		}
	}
	return 0;
}