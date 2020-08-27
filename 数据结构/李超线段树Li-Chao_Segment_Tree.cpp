#include <cstdio>
#include <algorithm>
#define N 39989
#define MAXN 40005
#define MAXT 160005
const double eps=1e-12;
const double inf=1e9;

using namespace std;

struct line{
	int l,r;
	double k,b;
	int id;
}sgt[MAXT];

double calc(line l,int x){return l.k*x+l.b;}

void modify(int cur,int l,int r,line li){
	if(li.l<=l && r<=li.r){
		if(calc(li,l)-calc(sgt[cur],l)>eps && calc(li,r)-calc(sgt[cur],r)>eps)
			sgt[cur]=li;
		else if(calc(li,l)-calc(sgt[cur],l)>eps || calc(li,r)-calc(sgt[cur],r)>eps){
			int mid=(l+r)>>1;
			if(calc(li,mid)-calc(sgt[cur],mid)>eps)
				swap(li,sgt[cur]);
			if(calc(li,l)-calc(sgt[cur],l)>eps)
				modify(cur<<1,l,mid,li);
			else modify(cur<<1|1,mid+1,r,li);
		}
	}
	else{
		int mid=(l+r)>>1;
		if(li.l<=mid) modify(cur<<1,l,mid,li);
		if(li.r>mid) modify(cur<<1|1,mid+1,r,li);
	}
}

line query(int cur,int l,int r,int x){
	if(l==r) return sgt[cur];
	else{
		int mid=(l+r)>>1;
		line t;
		if(x<=mid) t=query(cur<<1,l,mid,x);
		else t=query(cur<<1|1,mid+1,r,x);
		if(!t.id || calc(sgt[cur],x)-calc(t,x)>eps) return sgt[cur];
		else return t;
	}
}

void built(int cur,int l,int r){
	sgt[cur].k=sgt[cur].b=0;
	sgt[cur].l=1; sgt[cur].r=N;
	sgt[cur].id=0;
	if(l<r){
		int mid=(l+r)>>1;
		built(cur<<1,l,mid);
		built(cur<<1|1,mid+1,r);
	}
}

int n;

int main(){
	scanf("%d", &n);
	built(1,1,N);
	int last=0,id=0;
	for(int i=1;i<=n;i++){
		int opt;
		scanf("%d", &opt);
		if(opt==0){
			int x;
			scanf("%d", &x);
			x=(x+last-1)%N+1;
			printf("%d\n", last=query(1,1,N,x).id);
		}
		else{
			int x0,x1,y0,y1;
			scanf("%d %d %d %d", &x0,&y0,&x1,&y1);
			x0=(x0+last-1)%N+1;
			x1=(x1+last-1)%N+1;
			y0=(y0+last-1)%1000000000+1;
			y1=(y1+last-1)%1000000000+1;
			line t;
			t.id=++id;
			t.l=min(x0,x1); t.r=max(x0,x1);
			t.k=x1==x0?0:(double)(y1-y0)/(x1-x0);
			t.b=x1==x0?max(y0,y1):y0-t.k*x0;
			modify(1,1,N,t);
		}
	}
	return 0;
}