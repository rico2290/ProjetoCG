#include "luz.h"

luz::luz()
{

}
luz::luz(RGB _R, Point *_Pos){
    this->F=_R;
    this->P=_Pos;
}

void luz::Imp(){
    std::cout << "\nImp Luz"
              << "\nInt.: " << this->F.R << ", " << this->F.G << ", "<< this->F.B << ";"
              << "\nPos.: " << this->P->x << ", " << this->P->y << ", " << this->P->z <<";";
}
