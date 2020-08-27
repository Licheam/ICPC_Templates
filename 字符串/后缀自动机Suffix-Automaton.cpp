#include <bits/stdc++.h>
#define MAXN 1000005
#define LL long long
using namespace std;

struct SAM {
    int len,link,cnt;
    int ch[26];
}sam[MAXN<<1];

int sz,last;

void sam_init() {
    sam[0].len=0;
    sam[0].link=-1;
    sam[0].cnt=0;
    memset(sam[0].ch,0,sizeof(sam[0].ch));
    sz=0;
    last=0;
}

void sam_extend(int c) {
    int cur=++sz;
    sam[cur].len=sam[last].len+1;
    memset(sam[cur].ch,0,sizeof(sam[cur].ch));

    int p=last;
    for(;~p && !sam[p].ch[c];p=sam[p].link)
        sam[p].ch[c]=cur;

    if(!~p) {
        sam[cur].link=0;
    } else {
        int q=sam[p].ch[c];
        if(sam[p].len+1==sam[q].len) {
            sam[cur].link=q;
        } else {
            int clone=++sz;
            sam[clone]=sam[q];
            sam[clone].len=sam[p].len+1;
            sam[clone].cnt=0;
            sam[q].link=sam[cur].link=clone;
            for(;~p && sam[p].ch[c]==q;p=sam[p].link)
                sam[p].ch[c]=clone;
        }
    }
    
    last=cur;
    sam[cur].cnt=1;
}

struct edge{
    int to,next;
}e[MAXN<<1];

int tot,head[MAXN<<1];

void add(int x,int y) {
    tot++;
    e[tot].to=y;
    e[tot].next=head[x];
    head[x]=tot;
}

char s[MAXN];
LL ans;

void dfs(int x) {
    for(int p=head[x];p;p=e[p].next) {
        int u=e[p].to;
        dfs(u);
        sam[x].cnt+=sam[u].cnt;
    }
    if(sam[x].cnt!=1) ans=max(ans,1LL*sam[x].len*sam[x].cnt);
}

void solve() {
    scanf("%s", s);
    int len=strlen(s);
    sam_init();
    for(int i=0;i<len;i++)
        sam_extend(s[i]-'a');
    tot=0;
    memset(head,0,(sz+1)*sizeof(head[0]));
    for(int i=1;i<=sz;i++)
        add(sam[i].link,i);
    ans=0;
    dfs(0);
    printf("%lld\n", ans);
}

int main() {
    int T=1,cas=1;
    // scanf("%d", &T);
    while(T--) {
        // printf("Case #%d: ", cas++);
        solve();
    }
    return 0;
}