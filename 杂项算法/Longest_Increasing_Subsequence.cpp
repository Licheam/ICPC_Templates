#include <cstdio>
#include <functional>
#include <algorithm>
#include <map>
#include <utility>
#define MAXN 100005

using namespace std;

int n,a[MAXN],len;
map <int,int> mp,rmp;

int main(){
    scanf("%d", &n);
    for(int i=1,t;i<=n;i++){
        scanf("%d", &t);
        mp.insert(make_pair(t,i));
    }
    a[len=0]=0;
    map <int,int>::iterator ite;
    for(int i=1,t,v;i<=n;i++){
        scanf("%d",&t);
        ite=mp.find(t);
        v=ite->second;
        if(v>a[len])
            a[++len]=v;
        else{
            int *p=upper_bound(a+1,a+len+1,v,less<int>());
            *p=v;
        }
    }
    printf("%d\n",len);
    return 0;
}