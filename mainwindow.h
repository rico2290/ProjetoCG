#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cenario.h"
#include "v3.h"
#include "material.h"
#include "face.h"
#include "rgb.h"
#include "observador.h"
#include "operacoes.h"
#include "objeto.h"
#include "camera.h"
#include "luz.h"
#include "cenario.h"
#include "rgb.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool grama = false;
    bool quadra = false;
    bool cubos = false;
    bool traves = false;


    bool p1 = false;
    bool p2 = false;
    bool p3 = false;
    bool p4 = false;

    int sizeX = 800;
    int sizeY = 800;
    float W = 0.5;
    float H = 0.5;
    float d = 1;

    float Ex, Ey, Ez;
    float Lox, Loy, Loz;
    float Avx, Avy, Avz;

    Observador *Obs;
    Camera *Cam;

    RGB* Bg;
    RGB* Amb;
    Cenario* scene;

    float pF1x=0, pF1y=0, pF1z=0;
    float pF2x=0, pF2y=0, pF2z=0;
    float pF3x=0, pF3y=0, pF3z=0;
    float pF4x=0, pF4y=0, pF4z=0;
    float pF5x=0, pF5y=0, pF5z=0;

    Point *pF1;
    Point *pF2;
    Point *pF3;
    Point *pF4;
    Point *pF5;

    float rSp1 = 1, gSp1=1, bSp1=1;
    float rSp2 = 1, gSp2=1, bSp2=1;
    float rSp3 = 1, gSp3=1, bSp3=1;
    float rSp4 = 1, gSp4=1, bSp4=1;

    float dObq_x=0,dObq_y=0,dObq_z=-1;
    float FOb =0, Teta=0;

    Point *sP1;


    bool Renderiza_sombras = false;

    float rF1=0,rF2=0,rF3=0,rF4=0,rF5=0;
    float gF1=0,gF2=0,gF3=0,gF4=0,gF5=0;
    float bF1=0,bF2=0,bF3=0,bF4=0,bF5=0 ;

    Objeto* CuboUni3(Material *M);
    void cWord();

private:
    Ui::MainWindow *ui;

public slots:
    //void Obq();
    void Render();
    void MontaCena();
    void CamT();
    void Sair();
    void Pad();

    void setTeta(double);
    void setFator(double);

    void sombras_rend(bool);
    void RenderPFuga(Cenario *Cena);
    void RenderPFuga2(Cenario *Cena);
    void RenderPFuga3(Cenario *Cena);
    void Fuga_1P();
    void Fuga_2P();
    void Fuga_3P();

    void setPF1x(double);
    void setPF2x(double);
    void setPF3x(double);
    void setPF4x(double);
    void setPF5x(double);

    void setPF1y(double);
    void setPF2y(double);
    void setPF3y(double);
    void setPF4y(double);
    void setPF5y(double);

    void setPF1z(double);
    void setPF2z(double);
    void setPF3z(double);
    void setPF4z(double);
    void setPF5z(double);


    void setF1r(int);
    void setF1g(int);
    void setF1b(int);
    void setF2r(int);
    void setF2g(int);
    void setF2b(int);
    void setF3r(int);
    void setF3g(int);
    void setF3b(int);
    void setF4r(int);
    void setF4g(int);
    void setF4b(int);
    void setF5r(int);
    void setF5g(int);
    void setF5b(int);

    void setBG_R(int);
    void setBG_G(int);
    void setBG_B(int);
    void IA_R(int);
    void IA_G(int);
    void IA_B(int);



    void setGrama(bool);
    void setQuadra(bool);
    void setCubos(bool);
    void setTraves(bool);
    void setP1(bool);
    void setP2(bool);
    void setP3(bool);
    void setP4(bool);

    void Eye_X(double);
    void Eye_Y(double);
    void Eye_Z(double);

    void Lo_X(double);
    void Lo_Y(double);
    void Lo_Z(double);

    void Av_X(double);
    void Av_Y(double);
    void Av_Z(double);

    void setW(double);
    void setH(double);
    void setD(double);
    void setSX(double);
    void setSY(double);


    void set_rSp1(int);
    void set_gSp1(int);
    void set_bSp1(int);

    void set_rSp2(int);
    void set_gSp2(int);
    void set_bSp2(int);

    void set_rSp3(int);
    void set_gSp3(int);
    void set_bSp3(int);

    void set_rSp4(int);
    void set_gSp4(int);
    void set_bSp4(int);

};

#endif // MAINWINDOW_H
