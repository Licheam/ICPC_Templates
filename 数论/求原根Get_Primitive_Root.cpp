#include <cstdio>
#include <vector>

using namespace std;

int p;
vector<int> v;

int binpow(int x,int y,int mod){
	int r=1%mod;
	while(y){
		if(y&1) r=(1LL*r*x)%mod;
		x=(1LL*x*x)%mod;
		y>>=1;
	}
	return r;
}

int main(){
	scanf("%d", &p);
	int pp=p-1;
	for(int i=2;i*i<=pp;i++){
		if(pp%i==0){
			v.push_back(i);
			while(pp%i==0) pp/=i;
		}
	}
	if(pp>1) v.push_back(pp);
	for(int g=2;;g++){
		bool isg=true;
		for(int d:v){
			if(binpow(g,(p-1)/d,p)==1){
				isg=false;
				break;
			}
		}
		if(isg){
			printf("%d\n", g);
			break;
		}
	}
	return 0;
}