#ifndef CENARIO_H
#define CENARIO_H
#include "observador.h"
#include "operacoes.h"
#include "objeto.h"
#include "camera.h"
#include "luz.h"
#include "v3.h"
#include "rgb.h"
#include "material.h"
#include "spot.h"
#include "transformacoes.h"
class Cenario
{
public:
    Cenario();
    Cenario(Camera *_Cam,RGB* Ambiente ,RGB* BackGround, Observador *Obs);
    void addObjeto(Objeto *O);
    void addFonte(luz *L);
    void addFonte2(Point *P, RGB I);
    void addSpot(Spot *S);
    void addSpot2(Point *P,Point*D, RGB I, float A);
    void Word_Cam();
    float Ray_intersept(Point Po, Point D, int &iObj, int &iFace);
    RGB* Ray_Pix_Ilm(Point Po, Point D);
    RGB* Ilm_Pint(Point Pint, Point nFace, Material *MF);
    void CuboUni();
    void CuboUni2(Material *M1,Material *M2,Material *M3,Material *M4,Material *M5,Material *M6);
    void CuboUni3(Material *M);
    void Prisma_Triangular_Uni3(Material *M);
    void Libera();
    bool sombra(Point Pint, Point L);
    bool Renderiza_somb;
    RGB* Amb;
    RGB* BG;
    Observador *Obs;
    Camera *Cam;
    std::vector<Objeto*> Objetos;
    std::vector<luz*> fontes_luminosas;
    std::vector<Spot*> fontes_spot;
};

#endif // CENARIO_H
