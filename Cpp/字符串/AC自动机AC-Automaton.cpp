#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#define MAXN 1000006
using namespace std;

struct trie{
	int fail,mark,ch[26];
}tt[MAXN];

int tot;

void insert(char *s){
	int len=strlen(s+1), cur=0;
	for(int i=1;i<=len;i++){
		int& next=tt[cur].ch[s[i]-'a'];
		if(!next){
			next=++tot;
			tt[tot].mark=0;
		}
		cur=next;
	}
	tt[cur].mark++;
}

void getfail(){
	queue<int> Q;
	tt[0].fail=0;
	tt[0].mark=0;
	for(int i=0;i<26;i++)
		if(tt[0].ch[i]) tt[tt[0].ch[i]].fail=0, Q.push(tt[0].ch[i]);
	while(!Q.empty()){
		int u=Q.front(); Q.pop();
		for(int i=0;i<26;i++){
			if(!tt[u].ch[i]) continue;
			int k=tt[u].fail;
			while(k && !tt[k].ch[i])
				k=tt[k].fail;
			tt[tt[u].ch[i]].fail=tt[k].ch[i];
			// tt[tt[u].ch[i]].mark+=tt[tt[k].ch[i]].mark;//如果需要重复统计，fail累加标记
			Q.push(tt[u].ch[i]);
		}
	}
}

int query(char *s){
	int len=strlen(s+1),ans=0;
	for(int i=1,k=0;i<=len;i++){
		while(k && !tt[k].ch[s[i]-'a'])
			k=tt[k].fail;
		k=tt[k].ch[s[i]-'a'];
		ans+=tt[k].mark;

		tt[k].mark=0;//清除该字符串的标记（只求
	}
	return ans;
}

int n;
char s[MAXN];

int main(){
	scanf("%d", &n);
	tot=0;
	memset(tt,0,sizeof(tt));
	for(int i=1;i<=n;i++){
		scanf("%s", s+1);
		insert(s);
	}
	scanf("%s", s+1);
	getfail();
	printf("%d\n", query(s));
	return 0;
}