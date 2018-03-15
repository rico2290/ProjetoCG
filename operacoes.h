#ifndef OPERACOES_H
#define OPERACOES_H
#include <stdio.h>
#include <stdlib.h>
#include <v3.h>

class Operacoes
{
public:
    Operacoes();
    float** Identidade(int M);
    float** mult(int M, int N, int P, float **A, float **B);
    float** TrocaColuna (int M,int N, int P, int C1, int C2, float **matA);
    float** VetorColuna(Point *P);
    float* Gauss(int N, float **A, float *b);
    float* Vetor(Point P);
    Point normal(Point a, Point b);
    void ImprimeMat(int M, int N, float** Mat);

    void pEscalar(float E, int M, int N, float**A);
    float** sub(int M, int N, float** A, float** B);
    float** Transposta (int l, int c, float** A);
    float NormaVetor(int N, float* V);

    //Transformações
    float** Mat_Left_Quat(float* Q);
    float** Mat_Right_Quat(float* Q);
    float** Escala(int N, float*V);
    float** Cisalhamento(float A, int I1, int I2);
    float** Translacao(int N, float* V);
    float** EspelhoArb(int N, float** V);
    float** Rotacao(int N, int E,float A);
    float** Rotacao2(int N, int E, float Sen, float Cos);
    float** RotacaoArb(int N, float A, float* V);
    float** RQ(float A, float* V);
    void freeMat(int L, float** M);
};

#endif // OPERACOES_H
