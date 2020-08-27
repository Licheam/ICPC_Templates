#include <bits/stdc++.h>
#define MAXN 2100005

using namespace std;

const double PI=acos(-1);

struct Complex{
    double real,image;
    Complex operator+(Complex y)const{
        return {real+y.real,image+y.image};
    }
    Complex operator-(Complex y)const{
        return {real-y.real,image-y.image};
    }
    Complex operator*(Complex y)const{
        return {real*y.real-image*y.image,real*y.image+image*y.real};
    }
};

void FFT(int n,Complex* P,int f){
    for(int i=0,j=0;i<n;i++){
        if(i<j) swap(P[i],P[j]);
        for(int l=n>>1;(j^=l)<l;l>>=1);
    }

    for(int i=2,l;i<=n;i<<=1){
        l=i>>1;
        Complex wn={cos(2*PI/i),f*sin(2*PI/i)};
        for(int j=0;j<n;j+=i){
            Complex w={1,0};
            for(int k=0;k<l;k++,w=w*wn){
                Complex t=P[j+l+k]*w;
                P[j+l+k]=P[j+k]-t;
                P[j+k]=P[j+k]+t;
            }
        }
    }
}

int n,m,lim;
Complex A[MAXN],B[MAXN];

int main(){
    scanf("%d %d", &n, &m);
    for(lim=1;lim<=n+m;lim<<=1);
    memset(A,0,lim*sizeof(A[0]));
    memset(B,0,lim*sizeof(B[0]));
    for(int i=0,t;i<n+1;i++){
        scanf("%d", &t);
        A[i]={1.0*t,0};
    }
    for(int i=0,t;i<m+1;i++){
        scanf("%d", &t);
        B[i]={1.0*t,0};
    }
    FFT(lim,A,1);
    FFT(lim,B,1);
    for(int i=0;i<lim;i++)
        A[i]=A[i]*B[i];
    FFT(lim,A,-1);
    for(int i=0;i<n+m+1;i++)
        printf("%d ", (int)(A[i].real/lim+0.5));
    return 0;
}