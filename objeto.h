#ifndef OBJETO_H
#define OBJETO_H
#include<vector>
#include "stdio.h"
#include "v3.h"
#include "face.h"
#include "esfera.h"
#include "operacoes.h"
#include "material.h"
#include <fstream>
#include "transformacoes.h"
#define TAM 4

class Objeto
{
public:
    Objeto();

    void addPoint(float x, float y, float z);
    void addFace(int iP1, int iP2, int iP3, Material *M);
    void addFace2(int iP1, int iP2, int iP3);
    void addFace3(Point *P1, Point *P2, Point *P3, Material*M);
    float Ray_intersept(Point Po, Point Pint, int *ind);
    void calc_Esfera();
    void Transforoma(float A[TAM][TAM]);
    Objeto* Copia();
    void ImpPoints();
    bool Obstaculo(Point Pint, Point l);
    void Libera();
    Esfera Esf;
    std::vector<Point*> points;
    std::vector<Face*> faces;

};

#endif // OBJETO_H
