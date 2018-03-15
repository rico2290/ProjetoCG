#ifndef LUZ_H
#define LUZ_H
#include "rgb.h"
#include "v3.h"

class luz
{
public:
    luz();
    luz(RGB R, Point *Pos);
    RGB F;
    Point *P;
    void Imp();
};

#endif // LUZ_H
