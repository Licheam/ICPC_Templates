#include <cstdio>
#define MAXN 100005
const int inf=0x3f3f3f3f;

int root,len;

struct node{
	int v,fa,ch[2],size,cnt;
}sp[MAXN];

int getch(int x) {return sp[sp[x].fa].ch[1]==x;}
void pushup(int x) {sp[x].size=sp[x].cnt+sp[sp[x].ch[0]].size+sp[sp[x].ch[1]].size;}

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

void insert(int x){
	int cur=root,f=0;
	while(cur&&sp[cur].v!=x){
		f=cur;
		cur=sp[cur].ch[x>sp[cur].v];
	}
	if(cur)
		sp[cur].cnt++;
	else{
		cur=++len;
		sp[f].ch[x>sp[f].v]=cur;
		sp[cur].ch[0]=sp[cur].ch[1]=0;
		sp[cur].fa=f;
		sp[cur].v=x;
		sp[cur].cnt=sp[cur].size=1;
	}
	splay(cur);
}

void find(int x){
	int cur=root;
	while(x!=sp[cur].v && sp[cur].ch[x>sp[cur].v])
		cur=sp[cur].ch[x>sp[cur].v];
	splay(cur);
}

int kth(int x){
	if(sp[root].size<x) return 0;
	int cur=root;
	while(1){
		if(x<=sp[sp[cur].ch[0]].size)
			cur=sp[cur].ch[0];
		else if(x>sp[sp[cur].ch[0]].size+sp[cur].cnt){
			x-=sp[sp[cur].ch[0]].size+sp[cur].cnt;
			cur=sp[cur].ch[1];
		}
		else return sp[cur].v;
	}
}

int pre(int x){
	find(x);
	if(x>sp[root].v) return root;
	int cur=sp[root].ch[0];
	while(sp[cur].ch[1])
		cur=sp[cur].ch[1];
	return cur;
}

int succ(int x){
	find(x);
	if(x<sp[root].v) return root;
	int cur=sp[root].ch[1];
	while(sp[cur].ch[0])
		cur=sp[cur].ch[0];
	return cur;
}

void erase(int x){
	int last=pre(x),next=succ(x),del;
	splay(last);splay(next,last);
	del=sp[next].ch[0];
	if(sp[del].cnt>1){
		sp[del].cnt--;
		splay(del);
	}
	else{
		sp[next].ch[0]=0;
		sp[del].fa=0;
		sp[del]=sp[len];
		int f=sp[del].fa;
		sp[f].ch[(sp[f].ch[1]==len)]=del;
		sp[sp[del].ch[0]].fa=del;
		sp[sp[del].ch[1]].fa=del;
		if(root==len) root=del;
		len--;

	}
}


int n;
int main(){
	scanf("%d", &n);
	root=0;len=0;
	insert(-inf);insert(inf);
	sp[0].size=0;
	for(int i=1;i<=n;i++){
		int opt,x;
		scanf("%d %d", &opt, &x);
		if(opt==1){
			insert(x);
		}
		else if(opt==2){
			erase(x);
		}
		else if(opt==3){
			find(x);
			printf("%d\n", sp[sp[root].ch[0]].size);
		}
		else if(opt==4){
			printf("%d\n", kth(x+1));
		}
		else if(opt==5){
			printf("%d\n", sp[pre(x)].v);
		}
		else{
			printf("%d\n", sp[succ(x)].v);
		}
	}
	return 0;
}