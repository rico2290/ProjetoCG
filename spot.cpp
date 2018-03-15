#include "spot.h"

Spot::Spot()
{

}
Spot::Spot(luz *_l, Point *_dir, float A){
    this->Luz=_l;
    this->Direcao=_dir;
    this->Abertura=A;
}
