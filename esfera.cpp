#include "esfera.h"

Esfera::Esfera()
{
}
Esfera::Esfera(Point c, float r){
    this->centro=c;
    this->raio=r;

}
bool Esfera::Interseccao(Point r){
    float a = r.ProdutoEscalar(r);
    float b = r.ProdutoEscalar(this->centro);
    float c = this->centro.ProdutoEscalar(this->centro);
    c -=(this->raio*this->raio);
    float Delta = ((b*b)-4*a*c);
    bool ret=false;
    if(Delta>=0)
        ret = true;
    return ret;
}
