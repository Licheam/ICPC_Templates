/*
	fread and fwrite from flukehn
*/
struct Frw{
  char *TT,*tmo,but[(1<<15)+2],butt[(1<<15)+2],*bp,*bq;
  Frw(){bp=butt,bq=butt+(1<<15);}
  ~Frw(){fwrite(butt,1,bp-butt,stdout);}
  #define getc() ((TT==tmo&&(tmo=((TT=but)+fread(but,1,1<<15,stdin)),TT==tmo))?-1:*TT++)
  #define RX {char c,f=1;while(!isdigit(c=getc()))f=c!='-';x=c-'0';\
    while(isdigit(c=getc()))x=x*10+c-'0';return f?x:-x;}
  inline operator int(){int x;RX;}
  inline void pr(char x){*bp=x;(++bp==bq)?fwrite(butt,1,1<<15,stdout),bp=butt:0;}
  inline void operator ()(int x,char c=-1){
    if(x<0)pr('-'),x=-x;
    static int s[20];int p=0;
    do s[p++]=x%10,x/=10;while(x);
    for(int i=p-1;~i;--i)pr(s[i]+'0');
    if(~c)pr(c);
  }
}frw;