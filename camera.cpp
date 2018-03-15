#include "camera.h"

Camera::Camera()
{

}
Camera::Camera(float _w, float _h, float _d, int sizeX, int sizeY){
    this->w=_w;
    this->h=_h;
    this->d=_d;
    this->DX= _w/sizeX;
    this->DY= _h/sizeY;
}

