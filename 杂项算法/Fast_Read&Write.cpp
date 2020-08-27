#include <cstdio>

int read(){
	int ng=0,x=0;
	char ch=getchar();
	for(;ch<'0' || ch>'9';ch=getchar()) ng|=ch=='-';
	for(;ch>='0' && ch<='9';ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return ng?-x:x;
}

int write(){
	
}

int main(){
	return 0;
}