#include <cstdio>
#include <algorithm>
#include <complex>
#define MAXN 4000005

using namespace std;

complex<double> omg[MAXN],iomg[MAXN],temp[MAXN];

void init(int n){
	double PI=acos(-1);
	for(int i=0;i<n;i++){
		omg[i]=polar(1.0,2.0*PI*i/n);
		iomg[i]=conj(omg[i]);
	}
}

void FFT(int n,complex<double>* buffer,int offset,int step,complex<double>* omg){
	if(n==1) return;
	int m=n>>1;
	FFT(m,buffer,offset,step<<1,omg);
	FFT(m,buffer,offset+step,step<<1,omg);
	for(int i=0;i<m;i++){
		int pos=2*i*step;
		temp[i]=buffer[offset+pos]+omg[i*step]*buffer[offset+step+pos];
		temp[i+m]=buffer[offset+pos]-omg[i*step]*buffer[offset+step+pos];
	}
	for(int i=0;i<n;i++)
		buffer[offset+i*step]=temp[i];
}

int n,m,lim;
complex<double> A[MAXN],B[MAXN];

int main(){
	scanf("%d %d", &n, &m);
	for(lim=1;lim<=n+m;lim<<=1);
	fill(A,A+lim,complex<double>(0.0,0.0));
	fill(B,B+lim,complex<double>(0.0,0.0));
	for(int i=0,t;i<n+1;i++){
		scanf("%d", &t);
		A[i]+=t;
	}
	for(int i=0,t;i<m+1;i++){
		scanf("%d", &t);
		B[i]+=t;
	}
	init(lim);
	FFT(lim,A,0,1,omg);
	FFT(lim,B,0,1,omg);
	for(int i=0;i<lim;i++)
		A[i]=A[i]*B[i];
	FFT(lim,A,0,1,iomg);
	for(int i=0;i<n+m+1;i++)
		printf("%d ", (int)(A[i].real()/lim+0.5));
	return 0;
}