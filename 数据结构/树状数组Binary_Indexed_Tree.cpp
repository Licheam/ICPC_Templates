/*
	Coded with Leachim's ACM Template.
	No errors. No warnings. ~~
*/
#include <bits/stdc++.h>
#pragma GCC diagnostic ignored "-Wunused-const-variable"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#define LL long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-7;
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};
const int MAXN=2000005;

int n,m,bit[MAXN];

int lowbit(int x){
	return x&(-x);
}

void change(int x,int y){
	for(;x<=n;x+=lowbit(x))
		bit[x]+=y;
}

int sum(int x){
	int s=0;
	for(;x>0;x-=lowbit(x))
		s+=bit[x];
	return s;
}

void build() {
    for(int x=1;x<<1<=n;x<<=1)
        for(int i=x;i+x<=n;i+=x<<1)
            bit[i+x]+=bit[i];
}

void solve() {
	scanf("%d %d", &n, &m);
	for(int i=1;i<=n;i++) scanf("%d", &bit[i]);
	build();
	for(int i=1;i<=m;i++) {
		int opt,x,y;
		scanf("%d %d %d", &opt, &x, &y);
		if(opt==1) {
			change(x,y);
		} else {
			printf("%d\n", sum(y)-sum(x-1));
		}
	}
}

int main() {
	int T=1,cas=1;(void)(cas);
	// scanf("%d", &T);
	while(T--) {
		// printf("Case #%d: ", cas++);
		solve();
	}
	return 0;
}