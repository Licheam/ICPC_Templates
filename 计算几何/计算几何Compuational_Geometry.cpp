#include <bits/stdc++.h>
#define MAXN 2000005
#define LL long long
using namespace std;
const double PI=acos(-1.0);
const double inf=1e100;
const double eps=1e-7;

int sgn(double d) {
    if(abs(d)<eps) return 0;
    if(d>0) return 1;
    return -1;
}

int dcmp(double x,double y) {
    if(abs(x-y)<eps) return 0;
    if(x>y) return 1;
    return -1;
}

struct Point{
    double x,y;
    Point(double x=0, double y=0):x(x),y(y){}

    Point operator + (const Point& B) const{
        return Point(x+B.x,y+B.y);
    }
    Point operator - (const Point& B) const{
        return Point(x-B.x,y-B.y);
    }
    Point operator * (const double k) const{
        return Point(x*k,y*k);
    }
    Point operator / (const double k) const{
        return Point(x/k,y/k);
    }
    bool operator < (const Point B) {
        if(dcmp(x,B.x)==0)
            return dcmp(y,B.y)<0;
        else return dcmp(x,B.x)<0;
    }

    double operator * (const Point& B) const{//点积
        return x*B.x+y*B.y;
    }
    double operator ^ (const Point& B) const {//叉积
        return x*B.y-y*B.x;
    }
};

typedef Point Vector;

double Length(Vector A) {
    return sqrt(A*A);
}

double Angle(Vector A, Vector B) {//弧度
    return acos(A*B/Length(A)/Length(B));
}

double Area2(Vector A, Vector B){//求平行四边形面积
    return A^B;
}

Vector Rotate(Vector A, double rad) {//逆时针
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}

Vector Normal(Vector A) {//逆时针转90度，单位法向量
    double L=Length(A);
    return Vector(-A.y/L, A.x/L);
}

bool ToLeftTest(Vector A, Vector B) {//B是不是在A左边
    return sgn(A^B)>0;
}

struct Line {//点向式+两点。既可以line也可以seg
    Point p1,p2;//p1->p2
    Vector v;
    Line(Point p1, Point p2):p1(p1),p2(p2),v((p2-p1)/Length(p2-p1)){}
    Point point(double t) {//给t求点
        return p1+v*t;
    }
};
typedef Line Segment;

bool OnLine(Point P,Line l) {//判断点P是否在直线L上
    return sgn((P-l.p1)^l.v);
}

Point GetIntersection(Line l1, Line l2) {//求直线交点
    double t = (l2.v^(l1.p1-l2.p1))/(l1.v^l2.v);
    return l1.point(t);
}

double DistanceToLine(Point P, Line l) {//点到直线距离
    return abs(l.v^(P-l.p1));
}

Point GetProjection(Point P, Line l) {//求投影点
    return l.point((P-l.p1)*l.v);
}

bool OnSegment(Point P, Segment s) {
    return (OnLine(P,s) && sgn((s.p1-P)*(s.p2-P))<0);
}

bool InSegmentIntersection(Segment s1, Segment s2) {//不允许端点相交
    double c1=(s1.p2-s1.p1)^(s2.p1-s1.p1), c2=(s1.p2-s1.p1)^(s2.p2-s1.p1);
    double c3=(s2.p2-s2.p1)^(s1.p1-s2.p1), c4=(s2.p2-s2.p1)^(s1.p2-s2.p1);
    return (sgn(c1)*sgn(c2)<0 && sgn(c3)*sgn(c4)<0);
}

void solve() {

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