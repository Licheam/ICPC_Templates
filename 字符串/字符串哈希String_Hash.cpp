#include <cstdio>
#include <string>

#define BASE 307
#define MOD 5555567

int hsh(string x){
	int h=0,len=x.length();
	for(int i=0;i<len;i++){
		h=(h*BASE+x[i])%MOD;
	}
	return h;
}

int main(){
	return 0;
}