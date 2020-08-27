#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <complex>
#define MAXN 300005
#define MAXL 550005

using namespace std;

const double PI=acos(-1);
complex<double> omg[MAXL],iomg[MAXL];

void init(int n){
	for(int i=0;i<n;i++){
		omg[i]=polar(1.0,2.0*PI*i/n);
		iomg[i]=conj(omg[i]);
	}
}

void FFT(int n,complex<double>* P,complex<double>* w){
	for(int i=0,j=0;i<n;i++){
		if(i<j) swap(P[i],P[j]);
		for(int l=n>>1;(j^=l)<l;l>>=1);
	}
	
	for(int i=2,l;i<=n;i<<=1){
		l=i>>1;
		complex<double> t;
		for(int j=0;j<n;j+=i){
			for(int k=0;k<l;k++){
				t=P[j+l+k]*w[n/i*k];
				P[j+l+k]=P[j+k]-t;
				P[j+k]=P[j+k]+t;
			}
		}
	}
}

int n,m,lim;
char s1[MAXN],s2[MAXN];
complex<double> A[MAXL],B[MAXL],tA[MAXL],tB[MAXL],ans[MAXL];

int main(){
	scanf("%d %d", &m, &n);
	scanf("%s %s",s1,s2);
	for(int i=0;i<m;i++) A[m-i-1]=(s1[i]=='*'?0:s1[i]-'a'+1);
	for(int i=0;i<n;i++) B[i]=(s2[i]=='*'?0:s2[i]-'a'+1);
	for(lim=1;lim<n-1;lim<<=1);
	init(lim);
	fill(ans,ans+lim,complex<double>(0.0,0.0));

	for(int i=0;i<m;i++) tA[i]=A[i]*A[i]*A[i];
	for(int i=0;i<n;i++) tB[i]=B[i];
	fill(tA+m,tA+lim,complex<double>(0.0,0.0));
	fill(tB+n,tB+lim,complex<double>(0.0,0.0));
	FFT(lim,tA,omg);
	FFT(lim,tB,omg);
	for(int i=0;i<lim;i++) ans[i]+=tA[i]*tB[i];

	for(int i=0;i<m;i++) tA[i]=A[i];
	for(int i=0;i<n;i++) tB[i]=B[i]*B[i]*B[i];
	fill(tA+m,tA+lim,complex<double>(0.0,0.0));
	fill(tB+n,tB+lim,complex<double>(0.0,0.0));
	FFT(lim,tA,omg);
	FFT(lim,tB,omg);
	for(int i=0;i<lim;i++) ans[i]+=tA[i]*tB[i];

	for(int i=0;i<m;i++) tA[i]=A[i]*A[i];
	for(int i=0;i<n;i++) tB[i]=B[i]*B[i];
	fill(tA+m,tA+lim,complex<double>(0.0,0.0));
	fill(tB+n,tB+lim,complex<double>(0.0,0.0));
	FFT(lim,tA,omg);
	FFT(lim,tB,omg);
	for(int i=0;i<lim;i++) ans[i]-=complex<double>(2.0,0)*tA[i]*tB[i];

	FFT(lim,ans,iomg);

	int cnt=0;
	for(int i=m-1;i<n;i++)
		if((int)(ans[i].real()/lim+0.5)==0) cnt++;
	printf("%d\n", cnt);
	for(int i=m-1;i<n;i++)
		if((int)(ans[i].real()/lim+0.5)==0) printf("%d ", i-m+2);
	return 0;
}