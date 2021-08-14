/*
    圆的K次交，O(n^2)?
    [SPOJ]CIRU2
    代码来源网络。
*/

#include<bits/stdc++.h>
using namespace std;

namespace online {
const int maxn=1005;
const double eps=1e-12;
const double pi=acos(-1);
int dcmp(double x) {return fabs(x)<eps?0:(x<0?-1:1);}
struct circle {
    double x,y,r,angle;int d;
    circle() {}
    circle(double x,double y,double angle=0,int d=0)
        :x(x),y(y),angle(angle),d(d) {}
};
typedef circle Circle;
circle cir[maxn],tp[maxn<<1];
double area[maxn];
double sqr(double x) {return x*x;}
double dis(circle a,circle b) {return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));}
double cross(circle a,circle b,circle c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
int CirCrossCir(Circle p1, double r1,Circle p2, double r2,Circle &cp1,Circle &cp2) {
    double mx = p2.x - p1.x, sx = p2.x + p1.x, mx2 = mx * mx;
    double my = p2.y - p1.y, sy = p2.y + p1.y, my2 = my * my;
    double sq = mx2 + my2, d = -(sq - sqr(r1 - r2)) * (sq - sqr(r1 + r2));
    if (d + eps < 0)return 0;
    if (d < eps)d = 0;
    else d = sqrt(d);
    double x = mx * ((r1 + r2) * (r1 - r2) + mx * sx) + sx * my2;
    double y = my * ((r1 + r2) * (r1 - r2) + my * sy) + sy * mx2;
    double dx = mx * d, dy = my * d;
    sq *= 2;
    cp1.x = (x - dy) / sq;
    cp1.y = (y + dx) / sq;
    cp2.x = (x + dy) / sq;
    cp2.y = (y - dx) / sq;
    if (d > eps)return 2;
    else return 1;
}

bool circmp(const Circle& u, const Circle& v) {return dcmp(u.r - v.r) < 0;}
bool cmp(const Circle& u, const Circle& v) {
    if (dcmp(u.angle - v.angle))return u.angle < v.angle;
    return u.d > v.d;
}
double calc(Circle cir,Circle cp1,Circle cp2) {
    double ans = (cp2.angle - cp1.angle) * sqr(cir.r)
                 - cross(cir, cp1, cp2) + cross(Circle(0, 0), cp1, cp2);
    return ans / 2;
}

void CirUnion(Circle cir[], int n) {
    Circle cp1, cp2;
    sort(cir, cir + n, circmp);
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (dcmp(dis(cir[i], cir[j]) + cir[i].r - cir[j].r) <= 0)
                cir[i].d++;
    for (int i = 0; i < n; ++i) {
        int tn = 0, cnt = 0;
        for (int j = 0; j < n; ++j) {
            if (i == j)continue;
            if (CirCrossCir(cir[i], cir[i].r, cir[j], cir[j].r,
                            cp2, cp1) < 2)
                continue;
            cp1.angle = atan2(cp1.y - cir[i].y, cp1.x - cir[i].x);
            cp2.angle = atan2(cp2.y - cir[i].y, cp2.x - cir[i].x);
            cp1.d = 1;
            tp[tn++] = cp1;
            cp2.d = -1;
            tp[tn++] = cp2;
            if (dcmp(cp1.angle - cp2.angle) > 0)
                cnt++;
        }
        tp[tn++] = Circle(cir[i].x - cir[i].r, cir[i].y, pi, -cnt);
        tp[tn++] = Circle(cir[i].x - cir[i].r, cir[i].y, -pi, cnt);
        sort(tp, tp + tn, cmp);
        int p, s = cir[i].d + tp[0].d;
        for (int j = 1; j < tn; ++j) {
            p = s;
            s += tp[j].d;
            area[p] += calc(cir[i], tp[j - 1], tp[j]);
        }
    }
}

void get_area(int n,double *x,double *y,double *r,double *ar) {
    for(int i=0; i<n; i++) {
        cir[i].x=x[i],cir[i].y=y[i],cir[i].r=r[i];
        cir[i].d=1;
    }
    memset(area+1,0,n*sizeof(area[0]));
    CirUnion(cir,n);
    for(int i=1;i<=n;i++)
        ar[i]=area[i];
}
}

const int MAXN=1005;
double x[MAXN],y[MAXN],r[MAXN],area[MAXN];
int main() {
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++)
        scanf("%lf %lf %lf", &x[i], &y[i], &r[i]);
    online::get_area(n,x,y,r,area);
    for(int i=1;i<=n;i++) {
        area[i]-=area[i+1];
        printf("[%d] = %.3f\n", i, area[i]);
    }
    return 0;
}