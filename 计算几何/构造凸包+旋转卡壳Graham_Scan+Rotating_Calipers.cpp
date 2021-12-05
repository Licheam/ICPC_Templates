Point p[MAXN],cv[MAXN];

void solve(int n) {
    for(int i=1;i<=n;i++) {
         int x,y;
         scanf("%d %d", &x, &y);
         p[i]=Point(x,y);
    }
    sort(p+1,p+1+n);
    int j=1;
    for(int i=1;i<=n;i++) {
        while(j>2 && dcmp((cv[j-1]-cv[j-2])^(p[i]-cv[j-1]),0)<=0) j--;
        cv[j++]=p[i];
    }
    for(int i=n,k=j;i;i--) {
        while(j>k && dcmp((cv[j-1]-cv[j-2])^(p[i]-cv[j-1]),0)<=0) j--;
        cv[j++]=p[i];
    }
    j--;
    if(j==2) {
        printf("0\n");
        return;
    }
    n=j;
    int si=1,sj=1;
    for(int i=1;i<=n;i++) {
        if(dcmp(cv[i].x,cv[si].x)<0) si=i;
        if(dcmp(cv[i].x,cv[sj].x)>0) sj=i;
    }
    double res=inf;
    for(int i=si,j=sj;i!=sj || j!=si;) {
        res=min(res,Length(cv[i]-cv[j]));
        if(dcmp((cv[i%n+1]-cv[i])^(cv[j%n+1]-cv[j]),0)<0) {
            res=min(res,DistanceToLine(cv[j],Line(cv[i],cv[i%n+1])));
            i=i%n+1;
        } else {
            res=min(res,DistanceToLine(cv[i],Line(cv[j],cv[j%n+1])));
            j=j%n+1;
        }
    }
    printf("%.2f\n", ceil((res-eps)*100)/100);
}