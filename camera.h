#ifndef CAMERA_H
#define CAMERA_H
#include "observador.h"

class Camera
{
public:
    Camera();
    Camera(float w, float h, float d, int sizeX, int sizeY);
    float w,h,d,DX,DY;
};

#endif // CAMERA_H
