#include <cstdio>
#include <cstring>
#define MAXN 1000005

int n,m,cnt,next[MAXN];
char s1[MAXN],s2[MAXN];

void kmp(){
	next[0]=-1;
	for(int i=1,k=-1;i<=m;i++){
		//k初始值为-1. next数组可以查询boarder的boarder.
		while(~k && s2[k+1]!=s2[i])
			k=next[k];
		next[i]=++k;
	}

	cnt=0;
	for(int i=1,k=0;i<=n;i++){
		//匹配串前缀与模式串后缀比，上一位前缀的boarder的boarder也能匹配。
		while(~k && s2[k+1]!=s1[i])
			k=next[k];
		if(m==++k){
			cnt++;
			printf("%d\n", i-m+1);
		}
	}
}

int main(){
	scanf("%s %s", s1+1, s2+1);
	n=strlen(s1+1);
	m=strlen(s2+1);
	kmp();
	for(int i=1;i<=m;i++){
		printf("%d ", next[i]);
	}
	return 0;
}