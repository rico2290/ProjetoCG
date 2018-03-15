#include "operacoes.h"
#define PI 3.14159265

Operacoes::Operacoes()
{

}

float** Operacoes::mult(int M, int N, int P, float **A, float **B)
{
    float **C;

    C = (float **)malloc(sizeof(float)*M);
    for (int i = 0; i < M; i++)
        C[i] = (float *)malloc(sizeof(float)*P);

    for (int i = 0; i < M; i++)
        for (int j = 0; j < P; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++){
                float t = A[i][k] * B[k][j];
                C[i][j] += t;
            }
               //printf("\ni = %d; j=%d; C[i][j] = %f", i,j, matC[i][j]);
        }

    return C;
}
float** Operacoes::Identidade(int N)
{
    float **mat;
    mat = (float **)malloc(sizeof(float)*N);
    for (int i = 0; i < N; i++)
        mat[i] = (float *)malloc(sizeof(float)*N);

    for(int i =0; i< N;i++)
        for(int j =0; j < N; j++){
            if(i==j){
                mat[i][j]=1;
            }else{
                mat[i][j]=0;
            }

        }



    return mat;
}

float** Operacoes::TrocaColuna (int M,int N, int P, int C1, int C2, float **matA){
    float** Id, **Result;
    Id = Identidade(N);
    Id[C1][C1] = 0;
    Id[C1][C2] = 1;
    Id[C2][C2] = 0;
    Id[C2][C1] = 1;
    Result = mult(M,N,P,matA,Id);
    return Result;
}
float** Operacoes::VetorColuna(Point *P){
    float** v;
    v = (float**)malloc(sizeof(float)*(4));
    for (int i = 0; i < 4; i++)
        v[i] = (float *)malloc(sizeof(float));
    v[0][0]=P->x;
    v[1][0]=P->y;
    v[2][0]=P->z;
    v[3][0]=1;

    return v;
}
float* Operacoes::Gauss (int N, float **matA, float *vet2){
    float* vet1 = (float *)malloc(sizeof(float)*N);
    int* vetAux = (int *)malloc(sizeof(int)*N);
    for(int k=0;k<N;k++){
        vetAux[k] = k;
    }
    int i,j;
    float alfa;
     for(j=0;j<=(N-2);j++){
        for(i=(j+1);i < N;i++){
            if(matA[i][j]!=0){
                if(matA[j][j]==0){ //Pivotação
                    float MJ = 0;
                    int aux=0;

                    for(int k=j+1; k<N;k++){
                        if(matA[j][k]>MJ){
                            MJ = matA[j][k];
                            aux = k;
                            }
                    }
                    int NC = aux; //Nova Coluna
                    matA = TrocaColuna(N,N,N,j,NC,matA);
                    //imp(N,N,matA);
                    vetAux[j]=NC;
                    vetAux[NC]=j;
                }
                alfa = (-matA[i][j])/matA[j][j];
                matA[i][j] = 0;
                for(int k=(j+1); k < N; k++){
                    matA[i][k] = matA[i][k] + (matA[j][k]*alfa);
                }

                vet2[i] = vet2[i] + (vet2[j]*alfa);
                }
        }
    }

    for(i = (N-1); i >=0; i--){
        float soma = 0;
        for(int k = i+1; k < N; k++)
            soma += matA[i][k] * vet2[k];
        vet2[i] = (vet2[i]-soma)/matA[i][i];

    }

    for(int k=0;k<N;k++){
        vet1[k]=vet2[vetAux[k]];
    }
    free(vetAux);
    vetAux = NULL;
    return vet1;
}
float* Operacoes::Vetor(Point P){
    float* v=(float*)malloc(sizeof(float)*4);
    v[0]=P.x;
    v[1]=P.y;
    v[2]=P.z;
    v[3]=0;
    return v;
}
Point Operacoes::normal(Point a, Point b)
{
    Point p1;
    p1.x=(a.y*b.z)-(a.z*b.y);
    p1.y=(a.z*b.x)-(a.x*b.z);
    p1.z=(a.x*b.y)-(a.y*b.x);
    return p1;
}

void Operacoes::pEscalar(float E, int M, int N, float**A){
    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
            A[i][j]*=E;
}
float** Operacoes::sub(int M, int N, float** A, float** B){
    float** C = (float **)malloc(sizeof(float)*M);
    for (int i = 0; i < M; i++){
        C[i] = (float *)malloc(sizeof(float)*(N));
        for(int j=0; j<N;j++)
            C[i][j]=A[i][j]-B[i][j];
    }
    return C;
}
float** Operacoes::Transposta (int l, int c, float** A) {
  float **matA;
  matA = (float **)malloc(sizeof(float)*c);
  for (int i = 0; i < c; i++){
    matA[i] = (float *)malloc(sizeof(float)*(l));
    for(int j=0;j<l;j++)
        matA[i][j]=A[j][i];
  }
    return matA;
}
float Operacoes::NormaVetor(int N, float* V){
    float norma = 0;
    for(int i=0;i<N;i++)
        norma+=(V[i]*V[i]);
    norma = sqrt(norma);
    return norma;
}

void Operacoes::ImprimeMat(int L, int C, float **Mat){
    std::cout << "\n Matriz M : \n";
    for(int i=0;i<L;i++){
        std::cout << "\nLinha "<<i<<": ";
        for(int j=0;j<C;j++){
            std::cout << Mat[i][j] << " ";
        }

    }

}

float** Operacoes::Mat_Left_Quat(float* Q){
    float** q = this->Identidade(4);
    for(int i=0;i<4;i++){
        q[i][i]=Q[3];
        q[3][i]=-Q[i];
        q[i][3]=Q[i];
    }
    q[0][1]= -Q[2];
    q[0][2]=  Q[1];
    q[1][0]=  Q[2];
    q[1][2]= -Q[0];
    q[2][0]= -Q[1];
    q[2][1]=  Q[0];

    return q;
}
float** Operacoes::Mat_Right_Quat(float* Q){
    float** q = this->Identidade(4);
    for(int i=0;i<4;i++){
        q[i][i]=Q[3];
        q[3][i]=-Q[i];
        q[i][3]=Q[i];
    }
    q[0][1]=  Q[2];
    q[0][2]= -Q[1];
    q[1][0]= -Q[2];
    q[1][2]=  Q[0];
    q[2][0]=  Q[1];
    q[2][1]= -Q[0];

    return q;
}
//Matrizes de transformação
float** Operacoes::Escala(int N, float*V){
    float** E = this->Identidade(N);
    for(int i=0; i<N;i++)
        E[i][i]=V[i];
    return E;
}
//Cisalhamento;
float** Operacoes::Cisalhamento(float A, int I1, int I2){
    float T = tan(A*PI/180);
    float** C = this->Identidade(4);
    C[I2][I1] = T;
    return C;
}
float** Operacoes::Translacao(int N, float* V){
    float** T = this->Identidade(N);
    for(int i=0;i<N;i++)
        T[i][N-1]=V[i];
    return T;
}

float** Operacoes::EspelhoArb(int N, float** V){
    float** E = this->Identidade(N); //E = I -2n*nt
    V[3][0]=0;
    float** nt = this->Transposta(N,1,V);
    float** H = this->mult(N,1,N,V,nt);
    this->pEscalar(2,N,N,H);
    E=this->sub(N,N,E,H);
    return E;
}



float** Operacoes::Rotacao(int N, int E,float A){
    float** M = this->Identidade(N+1);
    float S = sin(A*PI/180);
    float C = cos(A*PI/180);
    for(int i=0;i<N;i++){
        if(i!=E)
            for(int j=0;j<N;j++)
                if(j!=E){
                    if(i!=j)
                        if((i>E && i!=0 && j!=1) || (j<E && j!=0))
                            M[i][j]=-S;
                        else
                            M[i][j]=S;

                    else
                        M[i][j]=C;
                }
    }
    return M;
}

float** Operacoes::Rotacao2(int N, int E, float Sen, float Cos){
    float** M = this->Identidade(N);
    float S = Sen;
    float C = Cos;
    for(int i=0;i<N;i++){
        if(i!=E)
            for(int j=0;j<N;j++)
                if(j!=E){
                    if(i!=j)
                        if((i>E && i!=0 && j!=1) || (j<E && j!=0))
                            M[i][j]=-S;
                        else
                            M[i][j]=S;

                    else
                        M[i][j]=C;
            }

    }
    return M;
}

float** Operacoes::RotacaoArb(int N, float A, float* V){
    float** Rot;
    float **Rx, **Ry, **Rz;
    float S, C, L, H;
    float aux = ((V[1]*V[1])+(V[2]*V[2]));
    L=sqrt(aux);
    S = V[1]/L;
    C = V[2]/L;
    Rx =this->Rotacao2(N,0,S,C);
    //printf("\nRotacao em x\n");imp(N,N,Rx);
    H = this->NormaVetor(N,V);
    S = V[0]/H;
    C = L/H;
    Ry = this->Rotacao2(N,1,S,C);
    Ry = this->Transposta(N,N,Ry);
    //printf("\nRotacao em y-\n");imp(N,N,Ry);
    Rz = Rotacao(N,2,A);
    //printf("\nRotacao em z\n");imp(N,N,Rz);
    Rot = this->mult(N,N,N,Ry,Rx);
    Rot = this->mult(N,N,N,Rz,Rot);
    Ry = this->Transposta(N,N,Ry);
    //printf("\nRotacao em y\n");imp(N,N,Ry);
    Rx = this->Transposta(N,N,Rx);
    //printf("\nRotacao em x-\n");imp(N,N,Rx);
    Rot = this->mult(N,N,N,Ry,Rot);
    Rot = this->mult(N,N,N,Rx,Rot);

    float **Id = this->Identidade(N+1);
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            Id[i][j]=Rot[i][j];
    return Id;
}

float** Operacoes::RQ(float A, float* V){
    A = A/2;
    float *q1, *q2, **Lq1, **Rq2, **rot;
    q1 = (float *)malloc(sizeof(float)*4);
    q2 = (float *)malloc(sizeof(float)*4);
    float mV=this->NormaVetor(4,V);
      for(int i=0;i<3;i++){
        float aux = (sin(A*PI/180)*(V[i]/mV));
        q1[i]= aux;
        q2[i]=-aux;
    }
    q1[3] = cos(A*PI/180);
    q2[3] = cos(A*PI/180);
    Lq1 = this->Mat_Left_Quat(q1);
    Rq2 = this->Mat_Right_Quat(q2);
    rot = this->mult(4,4,4,Lq1,Rq2);
    return rot;
}

void Operacoes::freeMat(int L, float **M){
    for(int i =0; i<L; i++)
        free(M[i]);
    M=NULL;
}
