#ifndef ESFERA_H
#define ESFERA_H
#include "v3.h"

class Esfera
{
public:
    Esfera();
    Esfera(Point c, float r);
    bool Interseccao(Point p);

    Point centro;
    float raio;
};

#endif // ESFERA_H
