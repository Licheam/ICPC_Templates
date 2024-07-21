#include <cstdio>

int gcd(int x,int y){
	if(!x || !y) return x+y;
	return gcd(y,x%y);
}

int n;

int main(){
	scanf("%d", &n);
	int g;
	scanf("%d", &g);
	if(g<0)g=-g;
	for(int i=2;i<=n;i++){
		int t;
		scanf("%d", &t);
		if(t<0) t=-t;
		g=gcd(g,t);
	}
	printf("%d\n", g);
	return 0;
}