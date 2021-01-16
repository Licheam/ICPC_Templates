#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005

int kmp(char *s1, char *s2, int *nxt){
    int n=strlen(s1+1),m=strlen(s2+1);

    nxt[0]=-1;
    for(int i=1,k=-1;i<=m;i++){
        //k初始值为-1. nxt数组可以查询boarder的boarder.
        while(~k && s2[k+1]!=s2[i])
            k=nxt[k];
        nxt[i]=++k;
    }

    int cnt=0;
    for(int i=1,k=0;i<=n;i++){
        //匹配串前缀与模式串后缀比，上一位前缀的boarder的boarder也能匹配。
        while(~k && s2[k+1]!=s1[i])
            k=nxt[k];
        if(m==++k){
            cnt++;
            printf("%d\n", i-m+1);
        }
    }
    return cnt;
}

char s1[MAXN],s2[MAXN];
int nxt[MAXN];

int main(){
    scanf("%s %s", s1+1, s2+1);
    kmp(s1,s2,nxt);
    int len=strlen(s2+1);
    for(int i=1;i<=len;i++){
        printf("%d ", nxt[i]);
    }
    return 0;
}