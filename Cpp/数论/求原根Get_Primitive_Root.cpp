#include <bits/stdc++.h>
using namespace std;

int binpow(int x,int y,int m){
    int r=1%m;
    while(y){
        if(y&1) r=1LL*r*x%m;
        x=1LL*x*x%m;
        y>>=1;
    }
    return r;
}

int Primitive_Root(int p){//只能求素数
    static vector<int> v;
    v.clear();
    int x=p-1;
    for(int i=2;i*i<=x;i++) {
        if(x%i==0){
            v.push_back(i);
            while(x%i==0) x/=i;
        }
    }
    if(x>1) v.push_back(x);
    for(int g=2;g<p;g++) {//原根一般很小
        bool flag=true;
        for(auto x:v) {
            if(binpow(g,(p-1)/x,p)==1){
                flag=false;
                break;
            }
        }
        if(flag) return g;
    }
    return 0;
}