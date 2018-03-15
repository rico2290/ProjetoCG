#ifndef OBSERVADOR_H
#define OBSERVADOR_H
#include "v3.h"
#include "transformacoes.h"
#define TAM 4

class Observador
{
public:
    Observador();
    Observador(Point Pos, Point Look_At, Point A_View_UP);
    Point Pos,i,j,k;
    void Word_Cam(float M[TAM][TAM]);
    void Cam_Word(float M[TAM][TAM]);
};

#endif // OBSERVADOR_H
