#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 500005
const int inf=0x3f3f3f3f;
using namespace std;

struct node{
	int v,fa,ch[2],cnt;//basic
	int size,sum,lm,rm,mm;//pushup
	int flip,color;//pushdown
}sp[MAXN];

int a[MAXN],len,root,recy[MAXN],rlen;

int getch(int x){return sp[sp[x].fa].ch[1]==x;}

void pushup(int x){
	int lc=sp[x].ch[0],rc=sp[x].ch[1];
	sp[x].size=sp[lc].size+sp[rc].size+sp[x].cnt;
	sp[x].sum=sp[lc].sum+sp[rc].sum+sp[x].v;
	sp[x].lm=max(sp[lc].lm, sp[lc].sum+sp[x].v+sp[rc].lm);
	sp[x].rm=max(sp[rc].rm, sp[rc].sum+sp[x].v+sp[lc].rm);
    sp[x].mm=max(max(sp[lc].mm,sp[rc].mm),sp[lc].rm+sp[x].v+sp[rc].lm);
}

void pushdown(int x){
	int lc=sp[x].ch[0],rc=sp[x].ch[1];
	if(sp[x].color!=inf){
		if(lc){
			sp[lc].v=sp[lc].color=sp[x].color;
			sp[lc].sum=sp[lc].size*sp[x].color;
		}
		if(rc){
			sp[rc].v=sp[rc].color=sp[x].color;
			sp[rc].sum=sp[rc].size*sp[x].color;
		}
		if(sp[x].color>0){
			if(lc) sp[lc].lm=sp[lc].rm=sp[lc].mm=sp[lc].sum;
			if(rc) sp[rc].lm=sp[rc].rm=sp[rc].mm=sp[rc].sum;
		}
		else{
			if(lc) {sp[lc].lm=sp[lc].rm=0; sp[lc].mm=sp[lc].v;}
			if(rc) {sp[rc].lm=sp[rc].rm=0; sp[rc].mm=sp[rc].v;}
		}
		sp[x].color=inf;
		sp[x].flip=0;
	}
	else if(sp[x].flip){
		if(lc){
			sp[lc].flip^=1;
			swap(sp[lc].ch[0],sp[lc].ch[1]);
			swap(sp[lc].lm,sp[lc].rm);
		}
		if(rc){
			sp[rc].flip^=1;
			swap(sp[rc].ch[0],sp[rc].ch[1]);
			swap(sp[rc].lm,sp[rc].rm);
		}
		sp[x].flip=0;
	}
}

void rotate(int x){
	int f=sp[x].fa, ff=sp[f].fa;
	int k=getch(x);
	sp[ff].ch[getch(f)]=x; sp[x].fa=ff;
	sp[sp[x].ch[k^1]].fa=f; sp[f].ch[k]=sp[x].ch[k^1];
	sp[x].ch[k^1]=f; sp[f].fa=x;
	pushup(f); pushup(x);
}

void splay(int x,int goal=0){
	for(int f;(f=sp[x].fa)!=goal;rotate(x)){
		if(sp[f].fa!=goal)
			rotate(getch(x)==getch(f)?f:x);
	}
	if(!goal) root=x;
}

int find(int x){
	int cur=root;
	while(1){
		pushdown(cur);
		if(x<=sp[sp[cur].ch[0]].size)
			cur=sp[cur].ch[0];
		else if(x>sp[sp[cur].ch[0]].size+sp[cur].cnt){
			x-=sp[sp[cur].ch[0]].size+sp[cur].cnt;
			cur=sp[cur].ch[1];
		}
		else return cur;
	}
}

int built(int f,int l,int r){
	if(l>r) return 0;
	int mid=(l+r)>>1, cur=rlen?recy[rlen--]:++len;
	sp[cur].v=a[mid];
	sp[cur].fa=f;
	sp[cur].cnt=1;
	sp[cur].flip=0;
	sp[cur].color=inf;
	sp[cur].ch[0]=built(cur,l,mid-1);
	sp[cur].ch[1]=built(cur,mid+1,r);
	pushup(cur);
	return cur;
}

void insert(int pos,int tot){
	int l=find(pos),r=find(pos+1);
	splay(l);splay(r,l);
	sp[r].ch[0]=built(r,1,tot);
	pushup(r); pushup(l);
}

void recycle(int x){
	if(!x) return;
	recycle(sp[x].ch[0]);
	recycle(sp[x].ch[1]);
	sp[sp[x].fa].ch[getch(x)]=0;
	recy[++rlen]=x;
}

void erase(int pos,int tot){
	int l=find(pos-1),r=find(pos+tot);
	splay(l);splay(r,l);
	recycle(sp[r].ch[0]);
	pushup(r); pushup(l);
}

void dye(int pos,int tot,int c){
	int l=find(pos-1),r=find(pos+tot);
	splay(l);splay(r,l);
	int x=sp[r].ch[0];
	sp[x].color=c;
	sp[x].v=c;
	sp[x].sum=sp[x].size*c;
	if(c>0)
		sp[x].lm=sp[x].rm=sp[x].mm=sp[x].sum;
	else{
		sp[x].lm=sp[x].rm=0;
		sp[x].mm=sp[x].v;
	}
	pushup(r); pushup(l);
}

void reverse(int pos,int tot){
	int l=find(pos-1),r=find(pos+tot);
	splay(l);splay(r,l);
	int x=sp[r].ch[0];
	sp[x].flip^=1;
	swap(sp[x].ch[0],sp[x].ch[1]);
	swap(sp[x].lm,sp[x].rm);
	pushup(r); pushup(l);
}

int getsum(int pos,int tot){
	int l=find(pos-1),r=find(pos+tot);
	splay(l);splay(r,l);
	return sp[sp[r].ch[0]].sum;
}

int n,m;

int main(){
	scanf("%d %d", &n, &m);
	for(int i=1;i<=n;i++){
		scanf("%d", &a[i+1]);
	}
	memset(sp,0,sizeof(sp[0]));
	sp[0].mm=a[1]=a[n+2]=-inf;
	rlen=0;
	len=0;
	root=built(0,1,n+2);
	for(int i=1;i<=m;i++){
		char opt[10];
		scanf("%s", opt);
		if(opt[0]=='I'){//Insert
			int pos,tot;
			scanf("%d %d", &pos, &tot);
			for(int i=1;i<=tot;i++)
				scanf("%d", &a[i]);
			insert(pos+1,tot);
		}
		else if(opt[0]=='D'){//Delete
			int pos,tot;
			scanf("%d %d", &pos, &tot);
			erase(pos+1,tot);
		}
		else if(opt[2]=='K'){//Make-Same
			int pos,tot,c;
			scanf("%d %d %d", &pos, &tot, &c);
			dye(pos+1,tot,c);
		}
		else if(opt[0]=='R'){//Reverse
			int pos,tot;
			scanf("%d %d", &pos, &tot);
			reverse(pos+1,tot);
		}
		else if(opt[0]=='G'){//Get-Sum
			int pos,tot;
			scanf("%d %d", &pos, &tot);
			printf("%d\n", getsum(pos+1,tot));
		}
		else if(opt[0]=='M'){//Max-Sum
			printf("%d\n", sp[root].mm);
		}
	}
	return 0;
}