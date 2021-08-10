/*
    MTT，即任意模数NTT（FFT实现）
    HDU7054，求\PI(1+x^ai)(\sum a_i<=1e5)
    启发式合并+ MTT(998244352)。
    【包含修改过的网络代码】
*/
#include <bits/stdc++.h>
namespace panda_2134 {//code from https://www.luogu.com.cn/blog/panda-2134/solution-p4245
const int MOD=998244352;
const int MAXN = 5e5+10;


typedef long long int64;
typedef long double D;

const D PI = acos(-1);

struct complex {
    D real, imag;
    complex() { real = imag = 0; }
    complex(D x): real(x), imag(0) {} 
    complex(D x, D y): real(x), imag(y) {}
    inline complex conj() { return complex(real, -imag); }
    inline complex operator+(complex rhs) const { return complex(real + rhs.real, imag + rhs.imag); }
    inline complex operator-(complex rhs) const { return complex(real - rhs.real, imag - rhs.imag); }
    inline complex operator*(complex rhs) const { return complex(real * rhs.real - imag * rhs.imag,
                                                                 imag * rhs.real + real * rhs.imag); }
    inline complex operator*=(complex rhs) { return (*this) = (*this) * rhs; }
    //(a+bi)(c+di) = (ac-bd) + (bc+ad)i
    friend inline complex operator*(D x, complex cp) { return complex(x * cp.real, x * cp.imag); }
    inline complex operator/(D x) const { return complex(real / x, imag / x); }
    inline complex operator/=(D x) { return (*this) = (*this) / x; }
    friend inline complex operator/(D x, complex cp) { return x * cp.conj() / (cp.real * cp.real - cp.imag * cp.imag); }
    inline complex operator/(complex rhs) const { 
        return (*this) * rhs.conj() / (rhs.real * rhs.real - rhs.imag * rhs.imag); 
    }
    inline complex operator/=(complex rhs) { return (*this) = (*this) / rhs; }
    inline D length() { return sqrt(real * real + imag * imag); }
};

inline complex get_omega(int len, bool inv) {
    return inv ? complex(std::cos(2*PI / len), -std::sin(2*PI / len))
                :complex(std::cos(2*PI / len),  std::sin(2*PI / len));
}

inline void fft(int len, complex* A, bool inv = false) {
    static int R[MAXN+10];
    for(int i = 0; i < len; i++)
        R[i] = ((R[i>>1]>>1) | (len >> (i&1))) & (len-1);
    for(int i = 0; i < len; i++)
        if(R[i] > i) std::swap(A[i], A[R[i]]);
    for(int step = 1; step < len; step <<= 1) 
        for(int i = 0; i < len; i += (step<<1)) {
            complex omega = 1, t = 0, rt = get_omega(step<<1, inv);
            for(int j = 0; j < step; j++, omega *= rt) {
                t = A[i+j+step] * omega;
                A[i+j+step] = A[i+j] - t;
                A[i+j] = A[i+j] + t;
            }
        }
    if(inv)
        for(int i = 0; i < len; i++)
            A[i] /= len;
}

//多项式最高系数分别为n,m，即长度为n+1,m+1。
void mtt(int n, int m, int *lhs, int *rhs, int *ret) {
    static complex A[MAXN+10], B[MAXN+10], C[MAXN+10], D[MAXN+10],
                   E[MAXN+10], F[MAXN+10], G[MAXN+10], H[MAXN+10];
    int len; for(len = 1; len < n+m+1; len<<=1);//len至少到n+m+1
    memset(lhs+n+1,0,(len-n)*sizeof(lhs[0]));
    memset(rhs+m+1,0,(len-m)*sizeof(rhs[0]));

    for(int i = 0; i < len; i++) {
        lhs[i] %= MOD; rhs[i] %= MOD;
        A[i] = lhs[i] >> 15; B[i] = lhs[i] & 0x7fff;
        C[i] = rhs[i] >> 15; D[i] = rhs[i] & 0x7fff;
    }
    fft(len, A); fft(len, B); fft(len, C); fft(len, D);
    for(int i = 0; i < len; i++) {
        E[i] = A[i] * C[i]; F[i] = B[i] * C[i];
        G[i] = A[i] * D[i]; H[i] = B[i] * D[i];
    }
    fft(len, E, true); fft(len, F, true); 
    fft(len, G, true); fft(len, H, true);
    for(int i = 0; i < len; i++)
        ret[i] = (((int64(round(E[i].real)) % MOD)<<30) % MOD + ((int64(round(F[i].real)) % MOD)<<15) % MOD
            + ((int64(round(G[i].real)) % MOD)<<15) % MOD + int64(round(H[i].real)) % MOD) % MOD;
}

}

using namespace std;
const int MOD=998244353;
const int MAXN=5e5+10;

int a[MAXN];
vector<int> v[MAXN];

struct cmp {
    bool operator()(int x,int y) const{
        return v[x].size()>v[y].size();
    }
};
    

priority_queue<int,vector<int>, cmp> Q;

int binpow(int x,int y,int m) {
    int r=1%m;
    while(y) {
        if(y&1) r=1LL*r*x%m;
        x=1LL*x*x%m;
        y>>=1;
    }
    return r;
}

void solve() {
    while(!Q.empty()) Q.pop();
    int n;
    scanf("%d", &n);
    int cnt=0;
    for(int i=1;i<=n;i++) {
        scanf("%d", &a[i]);
        if(!a[i]) cnt++;
        else {
            v[i].resize(a[i]+1);
            fill(v[i].begin(),v[i].end(),0);
            v[i][0]=1;
            v[i].back()=1;
            Q.push(i);
        }
    }
    if(cnt) {printf("0\n");return;}
    static int F[MAXN], G[MAXN], H[MAXN];
    while(Q.size()>1) {
        int i=Q.top();Q.pop();
        int j=Q.top();Q.pop();
        int n=v[i].size()-1;
        int m=v[j].size()-1;
        for(int k=0;k<=n;k++)
            F[k]=v[i][k];
        for(int k=0;k<=m;k++)
            G[k]=v[j][k];
        panda_2134::mtt(n,m,F,G,H);
        v[i].resize(n+m+1);
        for(int k=0;k<=n+m;k++)
            v[i][k]=H[k];
        Q.push(i);
    }
    int mi=Q.top();Q.pop();
    int ans=1;
    for(int i=1;i<v[mi].size();i++) {
        ans=(1LL*ans*binpow(i,v[mi][i],MOD))%MOD;
    }
    printf("%d\n", ans);
}

int main() {
    int T=1,cas=1;(void)(cas);
    scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}