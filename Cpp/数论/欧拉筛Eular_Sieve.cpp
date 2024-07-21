#include <cstdio>
#include <cstring>
#define MAXN 2000005

int cnt,p[MAXN];
bool inp[MAXN];
int phi[MAXN],mu[MAXN];

void eular_sieve(int n){
    cnt=0;
    memset(inp,0,(n+1)*sizeof(inp[0]));
    inp[0]=inp[1]=1;
    phi[1]=1;
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!inp[i]) p[++cnt]=i, phi[i]=i-1, mu[i]=-1;
        for(int j=1;j<=cnt && i*p[j]<=n;j++){
            inp[i*p[j]]=1;
            if(i%p[j]){
                phi[i*p[j]]=phi[i]*(p[j]-1);
                mu[i*p[j]]=-mu[i];
            }
            else{
                phi[i*p[j]]=phi[i]*p[j];
                mu[i*p[j]]=0;
                break;
            }
        }
    }
}

int main(){
    int n,m;
    scanf("%d %d", &n, &m);
    eular_sieve(n);
    for(int i=1;i<=m;i++){
        int k;
        scanf("%d",&k);
        printf("%d\n", p[k]);
    }
}