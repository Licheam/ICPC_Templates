#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 11000005
using namespace std;

int r[MAXN<<1],mx;
char st[MAXN<<1];

void manacher(char *s){
	int len=strlen(s);
	st[0]='$';
	for(int i=0;i<len;i++){
		st[i<<1|1]='#';
		st[(i+1)<<1]=s[i];
	}
	len=len<<1|1;
	st[len]='#';
	st[len+1]='*';
	r[1]=1;
	mx=0;
	for(int i=2,mid=1;i<=len;i++){
		r[i]=min(mid+r[mid]-i,r[2*mid-i]);
		for(;st[i-r[i]]==st[i+r[i]];r[i]++);
		if(i+r[i]>mid+r[mid]) mid=i;
		mx=max(mx,r[i]-1);
	}
}

char s[MAXN];

int main(){
	scanf("%s",s);
	manacher(s);
	printf("%d\n", mx);
	return 0;
}