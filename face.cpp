#include "face.h"
#include "operacoes.h"
#include "transformacoes.h"
Face::Face()
{

}
Face::Face(Point _P1, Point _P2, Point _P3){
    this->P1=&_P1;
    this->P2=&_P2;
    this->P3=&_P3;
    this->atNormal();
}


Face::Face(Point *_P1, Point *_P2, Point *_P3, Material *_M){
    this->P1=_P1;
    this->P2=_P2;
    this->P3=_P3;
    this->M =_M;
    this->N = this->calcNormal();

    //this->atNormal();
}

Face::Face(Point *_P1, Point *_P2, Point *_P3)
{
    this->P1=_P1;
    this->P2=_P2;
    this->P3=_P3;
    RGB pad(0.81176,0.81176,0.81176);
    this->M = new Material(pad,pad,pad,0.5);
    this->atNormal();

}
Point Face::calcNormal(){

    Point p1=*(this->P1);
    Point a=*(this->P2);
    Point b=*(this->P3);
    a.operator -=(p1);
    b.operator -=(p1);

    p1.x=(a.y*b.z)-(a.z*b.y);
    p1.y=(a.z*b.x)-(a.x*b.z);
    p1.z=(a.x*b.y)-(a.y*b.x);

    return p1;

}

float Face::Inter(Point P){
    float t = -1;

    Point p1,p2,p3;
    p1= *(this->P1);
    p2= *(this->P2);
    p3= *(this->P3);

    Point nF = this->N;
    Point Pint = P;
    float PE = Pint.ProdutoEscalar(nF);

    if(PE<0){
        Point v1 = p3;
        Point v2 = p3;
        v1.operator -=(p1);
        v2.operator -=(p2);

        transformacoes tr;
        float M[3][3];
        M[0][0] = v1.x; M[1][0] = v1.y; M[2][0] = v1.z;
        M[0][1] = v2.x; M[1][1] = v2.y; M[2][1] = v2.z;
        M[0][2] = P.x;  M[1][2] = P.y;  M[2][2] = P.z;
        float det = tr.Det3x3(M);
        tr.Inv3x3(M,det);
        Point lamb = tr.mxv(M,this->P3);

        float l3 = 1-(lamb.x+lamb.y);
        if(lamb.x>=0 && lamb.x<=1 && lamb.y>=0 && lamb.y<=1 && l3>=0 && l3<= 1 && lamb.z >= 1)
            t = lamb.z;


    }
    return t;

}

void Face::atNormal(){
    this->N= this->calcNormal();
}
bool Face::Obstaculo(Point Pint, Point l){

    Point p1,p2,p3;
    p1= *(this->P1);
    p2= *(this->P2);
    p3= *(this->P3);

    Point nF = this->N;
    float PE = l.ProdutoEscalar(nF);
    if(PE<0){

        Point v1 = p2;
        Point v2 = p3;
        v1.operator -=(p1);
        v2.operator -=(p1);

        transformacoes tr;
        float M[3][3];
        M[0][0] = v1.x; M[1][0] = v1.y; M[2][0] = v1.z;
        M[0][1] = v2.x; M[1][1] = v2.y; M[2][1] = v2.z;
        M[0][2] = -l.x;  M[1][2] = -l.y;  M[2][2] = -l.z;
        float det = tr.Det3x3(M);
        tr.Inv3x3(M,det);
        Point b = Pint;
        b.operator -=(p1);
        Point lamb = tr.mxv(M,&b);

        float l3 = 1-(lamb.x+lamb.y);

        if(lamb.x>=0 && lamb.x<=1 && lamb.y>=0 && lamb.y<=1 && l3>=0 && l3<=1 && lamb.z>0){
            //std::cout << "\n" << lamb.x << ", " << lamb.y << ", " << lamb.z;
            return true;

        }

    }
    return false;
}

void Face::Barycentric(Point p, Point a, Point b, Point c, float &u, float &v, float &w)
{
    Point v0 = b; Point v1 = c; Point v2 = p;
    v0.operator -=(a); v1.operator -=(a); v2.operator -=(a);

    //Vector v0 = b - a, v1 = c - a, v2 = p - a;
    float d00 = v0.ProdutoEscalar(v0);
    float d01 = v0.ProdutoEscalar(v1);
    float d11 = v1.ProdutoEscalar(v1);
    float d20 = v2.ProdutoEscalar(v0);
    float d21 = v2.ProdutoEscalar(v1);

    float denom = (d00 * d11) - (d01 * d01);

    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1-v-w;

}

float Face::Ray_intersept(Point Po, Point D){
    float t = -1;

    Point p1,p2,p3;
    p1= *(this->P1);
    p2= *(this->P2);
    p3= *(this->P3);

    Point nF = this->N;
    float PE = D.ProdutoEscalar(nF);
    if(PE<0){

        Point v1 = p2;
        Point v2 = p3;
        v1.operator -=(p1);
        v2.operator -=(p1);

        transformacoes tr;
        float M[3][3];
        M[0][0] = v1.x; M[1][0] = v1.y; M[2][0] = v1.z;
        M[0][1] = v2.x; M[1][1] = v2.y; M[2][1] = v2.z;
        M[0][2] = -D.x;  M[1][2] = -D.y;  M[2][2] = -D.z;
        float det = tr.Det3x3(M);
        tr.Inv3x3(M,det);
        Point b = Po;
        b.operator -=(p1);
        Point lamb = tr.mxv(M,&b);

        float l3 = 1-(lamb.x+lamb.y);

        if(lamb.x>=0 && lamb.x<=1 && lamb.y>=0 && lamb.y<=1 && l3>=0 && l3<=1 && lamb.z>0){
            //std::cout << "\n" << lamb.x << ", " << lamb.y << ", " << lamb.z;
            t = lamb.z;

        }

    }
    return t;
}
