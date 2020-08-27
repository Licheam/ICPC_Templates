#include <cstdio>
#include <algorithm>
#define LL long long
#define MAXN 100005
using namespace std;

struct line{
    int x,y1,y2,sign;
    bool operator<(line b)const{
    	if(x!=b.x) return x<b.x;
    	else return sign>b.sign;
    }
}li[MAXN<<1];

struct node{
	int le,ri;
	int cnt,len;
}sgt[MAXN<<3];

int dy[MAXN<<1];

void pushup(int cur){
	if(sgt[cur].cnt)
		sgt[cur].len=dy[sgt[cur].ri]-dy[sgt[cur].le];
	else if(sgt[cur].le<sgt[cur].ri-1)
		sgt[cur].len=sgt[cur<<1].len+sgt[cur<<1|1].len;
	else sgt[cur].len=0;
}

void build(int cur,int l,int r){
	sgt[cur].le=l, sgt[cur].ri=r;
	sgt[cur].cnt=sgt[cur].len=0;
	if(l<r-1){
		build(cur<<1,l,(l+r)>>1);
		build(cur<<1|1,(l+r)>>1,r);
	}
}

void modify(int cur,int l,int r,int sign){
	if(l<=sgt[cur].le && sgt[cur].ri<=r){
		sgt[cur].cnt+=sign;
	}
	else{
		int mid=(sgt[cur].le+sgt[cur].ri)>>1;
		if(l<mid) modify(cur<<1,l,r,sign);
		if(r>mid) modify(cur<<1|1,l,r,sign); 
	}
	pushup(cur);
}


int main(){
    int n,cnt;
    scanf("%d", &n);
    cnt=0;
    for(int i=1;i<=n;i++){
        int x1,y1,x2,y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        li[(i<<1)-1].x=x1, li[i<<1].x=x2;
        li[(i<<1)-1].y1=li[i<<1].y1=y1;
        li[(i<<1)-1].y2=li[i<<1].y2=y2;
        li[(i<<1)-1].sign=1, li[i<<1].sign=-1;
        dy[++cnt]=y1, dy[++cnt]=y2;
    }
    sort(dy+1,dy+cnt+1);
    cnt=unique(dy+1,dy+cnt+1)-dy-1;
    for(int i=1;i<=(n<<1);i++){
        li[i].y1=lower_bound(dy+1,dy+cnt+1,li[i].y1)-dy;
        li[i].y2=lower_bound(dy+1,dy+cnt+1,li[i].y2)-dy;
    }
    sort(li+1,li+(n<<1)+1);
    build(1,1,cnt);
    LL sum=0;
    for(int i=1;i<(n<<1);i++){
    	modify(1,li[i].y1,li[i].y2,li[i].sign);
    	sum+=1LL*sgt[1].len*(li[i+1].x-li[i].x);
    }
    printf("%lld\n", sum);
    return 0;
}