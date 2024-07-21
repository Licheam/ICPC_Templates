#include <bits/stdc++.h>
#define MAXN 1005

int n;

double ansx,ansy;

struct point{
	double x,y,w;
}p[MAXN];

double f(double x,double y){
	double sum=0.0;
	for(int i=1;i<=n;i++){
		double dx=x-p[i].x,dy=y-p[i].y;
		sum+=sqrt(dx*dx+dy*dy)*p[i].w;
	}
	return sum;
}

void SA(){
	double T=3000,d=0.999,tt=1e-15;
	while(T>tt){
		double newx=ansx+(2*rand()-RAND_MAX)*T;
		double newy=ansy+(2*rand()-RAND_MAX)*T;
		double delta=f(newx,newy)-f(ansx,ansy);
		if(delta<0 || exp(-delta/T)*RAND_MAX>rand()){
			ansx=newx;
			ansy=newy;
		}
		T*=d;
	}
}

int main(){
	srand(time(0));
	scanf("%d", &n);
	for(int i=1;i<=n;i++){
		scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].w);
	}
	ansx=ansy=0.0;
	for(int i=1;i<=n;i++){
		ansx+=p[i].x;
		ansy+=p[i].y;
	}
	ansx/=n;
	ansy/=n;
	SA();
	printf("%.3lf %.3lf\n", ansx, ansy);
	return 0;
}