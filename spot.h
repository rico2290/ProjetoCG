#ifndef SPOT_H
#define SPOT_H
#include "luz.h"
#include "v3.h"

class Spot
{
public:
    Spot();
    Spot(luz *_l, Point* _dir, float A);
    luz *Luz;
    Point* Direcao;
    float Abertura;
};

#endif // SPOT_H
