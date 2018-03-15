#ifndef POINT_H
#define POINT_H
#include "cmath"
#include <iostream>
class Point
{
public:
    Point();
    Point(float _x, float _y, float _z);

    Point operator+(Point P) const {
              return Point(x + P.x, y + P.y, z + P.z);
          }
          Point& operator+=(Point P) {
              x += P.x; y += P.y; z += P.z;
              return *this;
          }
          Point& operator*=(float Esc) {
              x *= Esc; y *= Esc; z *= Esc;
              return *this;
          }
          Point& operator-=(Point P){
              x -= P.x; y -= P.y; z -= P.z;
              return *this;
          }

          Point operator/(float div) const {
              return Point(x/div, y/div, z/div);
          }
          Point& operator/=(float div) {
              x /= div; y/= div; z /= div;
              return *this;
          }

          void normalize(){
              float len = sqrt(x*x + y*y + z*z );
              x/=len; y /= len; z /= len;
          }
          float ProdutoEscalar(Point P2);
          void ImpPoint();

        float x,y,z;
};

#endif // POINT_H
