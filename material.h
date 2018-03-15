#ifndef MATERIAL_H
#define MATERIAL_H
#include "rgb.h"


class Material
{
public:
    Material();
    Material(RGB A, RGB D, RGB E, int m);

    RGB A,D,E;
    int m;
};

#endif // MATERIAL_H
