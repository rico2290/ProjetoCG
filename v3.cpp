#include "v3.h"

Point::Point()
{

}
Point::Point(float _x, float _y, float _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
}

float Point::ProdutoEscalar(Point P){
    float x= (this->x*P.x)+(this->y*P.y)+(this->z*P.z);
    return x;
}
void Point::ImpPoint(){
    std::cout << "\nCoor.: " << this->x <<", "<< this->y<<", "<< this->z <<"; ";
}
