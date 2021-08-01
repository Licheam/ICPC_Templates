/*
    O(n)，求字符串字典序最小的循环表示
    [Luogu]1368
*/

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=2000005;

int a[MAXN];

void solve() {
    int n;
    scanf("%d", &n);
    //下标从0开始
    for(int i=0;i<n;i++)
        scanf("%d", &a[i]);

    int k=0,l=0,r=1;
    while(k<n && l<n && r<n) {
        if(a[(l+k)%n]==a[(r+k)%n])
            k++;
        else {
            if(a[(l+k)%n]>a[(r+k)%n]) l+=k+1;
            else r+=k+1;
            if(l==r) r++;
            k=0;
        }
    }
    l=min(l,r);
    for(int i=0;i<n;i++)
        printf("%d%c", a[(l+i)%n], " \n"[i==n-1]);
}

int main() {
    int T=1,cas=1;(void)(cas);
    // scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}