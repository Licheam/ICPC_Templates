/*
	决策单调性 + WQS二分

	给定数列{a}。设立k个关键点。
	让sigma min|a_i-b_k| 最小（每个a_i到最近的关键点距离之和）
*/
#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=2000005;

LL a[MAXN],f[MAXN];
int cnt[MAXN],lb[MAXN],rb[MAXN],p[MAXN];

LL w(int x,int y){
	return a[y]+a[x]-a[(x+y+1)>>1]-a[(x+y)>>1];
}

int k,n;

int calc(LL d) {
	int h,t;
	h=t=1;
	lb[t]=1,rb[t]=n,p[t]=0;
	f[0]=cnt[0]=0;
	for(int i=1;i<=n;i++) {
		f[i]=f[p[h]]+w(p[h],i)+d;
		cnt[i]=cnt[p[h]]+1;

		while(rb[h]<=i) h++;
		if(h<=t && lb[h]<=i) lb[h]=i+1;

		if(h<=t && f[i]+w(i,n)>f[p[t]]+w(p[t],n)) continue;
		while(h<=t && f[i]+w(i,lb[t])<=f[p[t]]+w(p[t],lb[t])) t--;
		if(h<=t) {
			int l=lb[t],r=rb[t]+1;
			while(l<r) {
				int mid=(l+r)>>1;
				if(f[i]+w(i,mid)<=f[p[t]]+w(p[t],mid)) r=mid;
 				else l=mid+1;
			}
			rb[t]=l-1;
			++t;
			lb[t]=l,rb[t]=n,p[t]=i;
		} else {
			++t;
			lb[t]=i,rb[t]=n,p[t]=i;
		}
	}
	return cnt[n];
}

void solve() {
	scanf("%d %d", &n, &k);
	a[0]=0;
	for(int i=1;i<=n;i++) {
		scanf("%lld", &a[i]);
		a[i]+=a[i-1];
	}

	LL l=0,r=a[n];
	while(l<r) {
		LL mid=(l+r+1)>>1;
		if(calc(mid)>=k) l=mid;
		else r=mid-1;
	}
	calc(l);

	printf("%lld\n", f[n]-1LL*k*l);
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