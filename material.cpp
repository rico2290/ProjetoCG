#include "material.h"

Material::Material()
{

}

Material::Material(RGB _A, RGB _D, RGB _E, int _m){
    this->A=_A;
    this->D=_D;
    this->E=_E;
    this->m=_m;

}
