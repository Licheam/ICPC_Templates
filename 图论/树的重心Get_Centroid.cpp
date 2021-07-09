/*
	求树的重心O(n) POJ1655
	以树的重心为根时，所有子树的大小都不超过整棵树大小的一半。
	树中所有点到某个点的距离和中，到重心的距离和是最小的；如果有两个重心，那么到它们的距离和一样。
	把两棵树通过一条边相连得到一棵新的树，那么新的树的重心在连接原来两棵树的重心的路径上。
	在一棵树上添加或删除一个叶子，那么它的重心最多只移动一条边的距离。
*/
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=2000005;

struct edge {
	int to,next;
}e[MAXN<<1];

int tot,head[MAXN];

void add(int x,int y) {
	tot++;
	e[tot].to=y;
	e[tot].next=head[x];
	head[x]=tot;
}

int n;
int size[MAXN],weight[MAXN];
vector<int> centroid;

void get_centroid(int x,int f) {
	size[x]=1;
	weight[x]=0;
	for(int p=head[x];p;p=e[p].next) {
		int u=e[p].to;
		if(u==f) continue;
		get_centroid(u,x);
		size[x]+=size[u];
		weight[x]=max(weight[x],size[u]);
	}
	weight[x]=max(weight[x],n-size[x]);
	if(weight[x]*2<=n)
		centroid.push_back(x);
}

void solve() {
	scanf("%d", &n);
	tot=0;
	memset(head+1,0,n*sizeof(head[0]));
	for(int i=1;i<n;i++) {
		int f,g;
		scanf("%d %d", &f, &g);
		add(f,g);
		add(g,f);
	}
	centroid.clear();
	get_centroid(1,1);
	sort(centroid.begin(), centroid.end());
	printf("%d %d\n", centroid[0], weight[centroid[0]]);
}

int main() {
	int T=1,cas=1;(void)(cas);
	scanf("%d", &T);
	while(T--) {
		// printf("Case #%d: ", cas++);
		solve();
	}
	return 0;
}