#ifndef RGB_H
#define RGB_H


class RGB
{
public:
    RGB();
    RGB(float R, float G, float B);
    void Normalize();
    float R,G,B;
};

#endif // RGB_H
