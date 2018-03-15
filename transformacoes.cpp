#include "transformacoes.h"

transformacoes::transformacoes()
{

}

void transformacoes::Identidade(float I[TAM][TAM]){
    for(int i=0; i<TAM;i++){
        for(int j=0;j<TAM;j++){
            if(i==j)
                I[i][j]=1;
            else
                I[i][j]=0;
        }
    }
}

void transformacoes::Translacao(float T[TAM][TAM], float t[TAM]){
    this->Identidade(T);
    for(int i=0;i<(TAM-1);i++)
        T[i][TAM-1]=t[i];

}

void transformacoes::Escala(float E[TAM][TAM], float e[TAM]){
    this->Identidade(E);
    for(int i=0;i<(TAM-1);i++)
        E[i][i]=e[i];
}

void transformacoes::MxM(float A[TAM][TAM], float B[TAM][TAM], float C[TAM][TAM]){
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++) {
            C[i][j] = 0;
            for (int k = 0; k < TAM; k++)
                C[i][j] += A[i][k] * B[k][j];
        }

}

void transformacoes::MxV(float M[TAM][TAM], Point *P){

    float vP[TAM]={P->x, P->y, P->z,1};
    float vPt[TAM]={0,0,0,0};
    for(int i=0;i<TAM-1;i++){
        for(int j=0;j<TAM;j++)
            vPt[i]+=M[i][j]*vP[j];
    }
    P->x=vPt[0];
    P->y=vPt[1];
    P->z=vPt[2];
}

void transformacoes::Imp(float M[TAM][TAM]){
    std::cout << "\n Matriz M["<<TAM<<"]["<<TAM<<"]: ";
    for(int i=0; i<TAM;i++){
        std::cout << "\n";
        for(int j=0;j<TAM;j++)
            std::cout << M[i][j] << " | ";
    }
}

float transformacoes::Det3x3(float m[TAM-1][TAM-1]){

    return m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
                 m[0][1] *(m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
                 m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
        /*DetA = a11.a22.a33 + a12.a23.a31 + a13.a21.a32 – a31.a22.a13 – a32.a23.a11 – a33.a21.a12*/
}

void transformacoes::Inv3x3(float Inv[TAM-1][TAM-1], float det){
    float m[3][3];
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            m[i][j] = Inv[i][j];

    float iD = 1/det;
    Inv[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * iD;
    Inv[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * iD;
    Inv[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * iD;
    Inv[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * iD;
    Inv[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * iD;
    Inv[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) * iD;
    Inv[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * iD;
    Inv[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]) * iD;
    Inv[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * iD;

    /*min  = (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) * invdet;
minv(0, 1) = (m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2)) * invdet;
minv(0, 2) = (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * invdet;
minv(1, 0) = (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) * invdet;
minv(1, 1) = (m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0)) * invdet;
minv(1, 2) = (m(1, 0) * m(0, 2) - m(0, 0) * m(1, 2)) * invdet;
minv(2, 0) = (m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1)) * invdet;
minv(2, 1) = (m(2, 0) * m(0, 1) - m(0, 0) * m(2, 1)) * invdet;
minv(2, 2) = (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1)) * invdet;*/

}

Point transformacoes::mxv(float M[TAM-1][TAM-1], Point *P){

        float vP[TAM-1]={P->x, P->y, P->z};
        float vPt[TAM-1]={0,0,0};
        for(int i=0;i<TAM-1;i++){
            for(int j=0;j<TAM-1;j++)
            vPt[i]+=M[i][j]*vP[j];
        }
        Point px(vPt[0],vPt[1],vPt[2]);
        return px;

}
