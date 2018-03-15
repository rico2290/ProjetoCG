#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "transformacoes.h"
#include "QImage"
#define PI 3.14159265

RGB G(0.4196,0.5568,0.1372);
RGB Qua(0.3235, 0.3823, 0.4450);
RGB Tra(1, 1, 1);
RGB C1(0.980392157,0.501960784, 0.4470588245);
RGB C2(1, 1, 1);
RGB C3(0, 1, 0);

RGB Az(72/255,118/255,1);
RGB J(1,1,1);
RGB P1(1,0,0);
RGB P2(0,1,0);
RGB P3(0,0,1);

RGB Esp(0,0,0);

Material *Cubo1 = new Material(C1,C1,C1,1);
Material *Cubo2 = new Material(C2,C2,C2,1);
Material *Cubo3 = new Material(C3,C3,C3,1);
Material *Grama = new Material(G,G,G,1);
Material *Quadra = new Material(Qua,Qua,Qua,1);
Material *Trave = new Material(Tra,Tra,Tra,1);



  float E[4][4], T[4][4], MT[4][4];
  float ve[4],vt[4];
  Objeto *O;

 transformacoes t;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Config
    Ex=-200; Ey=200;Ez=-200;
    Lox=50; Loy=0;Loz=50;
    Avx=50; Avy=100; Avz=50;
    Bg = new RGB(0.22,0.22,0.22);
    Amb = new RGB(0.1, 0.1, 0.1);

    Fuga_1P();
    Fuga_2P();
    Fuga_3P();

    Point Eye(Ex, Ey, Ez);
    Point LA(Lox,Loy,Loz);
    Point AVUp(Avx,Avy,Avz);

    Obs = new Observador(Eye,LA,AVUp);
    Cam = new Camera(W,H,-d,sizeX,sizeY);
    scene = new Cenario(Cam, Amb, Bg, Obs);

    pF1 = new Point(pF1x,pF1y,pF1z);


    sombras_rend(true);
    setGrama(true);
    setCubos(true);
    setQuadra(true);
    setTraves(true);

    setPF1x(100.0); // Posicao da Luz
    setPF1y(100.0);
    setPF1z(20.0);

    setF1r(255); // Cor da Luz
    setF1g(255);
    setF1b(255);

    Render();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Renhttps://rico2290@bitbucket.org/rico2290/projetofinalcg.gitder(){
    CamT();
    MontaCena();

    scene->Word_Cam();
    Point Po(0,0,0);
    QImage image = QImage( sizeX, sizeY, QImage::Format_RGB32 );
    for( int i=0; i<sizeX; i++){

        float Yi= (scene->Cam->h/2)-(scene->Cam->DY/2)-(i*scene->Cam->DY);


        for( int j=0; j<sizeY; j++ ){


            float Xj = (-scene->Cam->w/2)+(scene->Cam->DX/2)+(j*scene->Cam->DX);
            Point Pij(Xj,Yi,scene->Cam->d);
            Pij.normalize();

                RGB* print = scene->Ray_Pix_Ilm(Po, Pij);
                image.setPixel( j, i, qRgb(print->R*255, print->G*255, print->B*255));
        }https://rico2290@bitbucket.org/rico2290/projetofinalcg.git
    }

    QGraphicsScene * graphic = new QGraphicsScene( this );
    graphic->addPixmap( QPixmap::fromImage( image ) );
    ui->graphicsView->setScene(graphic);

    scene->Libera();
    free(scene);
}
void MainWindow::MontaCena(){

    ve[3] = 1; vt[3]=1;
    int iobj =-1;
    if(grama){
            O = CuboUni3(Grama);
            ve[0] = 110;ve[1] = 0.8; ve[2] = 100;
            t.Escala(E,ve);
            O->Transforoma(E);
            scene->Objetos.push_back(O);
            iobj++;
        }
        if(quadra){
            //estrada
            O = CuboUni3(Quadra);
            ve[0]=40;ve[1]=0.2;ve[2]=100;
            vt[0]=30;vt[1]=0.7;vt[2]=0;
            t.Escala(E,ve);
            t.Translacao(T,vt);
            t.MxM(T,E,MT);;
            O->Transforoma(MT);
            scene->Objetos.push_back(O);
            iobj++;        

        }
        if(cubos){
            //predio esq
            //ve0 espessura do cubo, ve1 altura do cubo, ve2 comprimento dir
           // vt0 dist pra frente, vt1-altura do chão, vt2 - dist pra esq
                O = CuboUni3(Cubo1);
                ve[0]=15;ve[1]=50;ve[2]=50;
                vt[0]=80;vt[1]=0.0;vt[2]=9;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

              //Topo da construção esq
               //ve1 espessura do cubo, ve2 altura do cubo, ve2 comprimento dir
               O = CuboUni3(Cubo2);
               ve[0]=18;ve[1]=3;ve[2]=53;
               vt[0]=80;vt[1]=50;vt[2]=9;
               t.Escala(E,ve);
               t.Translacao(T,vt);
               t.MxM(T,E,MT);
               O->Transforoma(MT);
               scene->Objetos.push_back(O);
               iobj++;

               //passeio da construção esq
                //ve1 espessura do cubo, ve2 altura do cubo, ve2 comprimento dir
                O = CuboUni3(Cubo2);
                ve[0]=10;ve[1]=3;ve[2]=80;
                vt[0]=70;vt[1]=0;vt[2]=0;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

               //div predio esq
               O = CuboUni3(Cubo2);
               ve[0]=2;ve[1]=5;ve[2]=50;// ve2 comprimento/largura (dir)
               vt[0]=78;vt[1]=30;vt[2]=7; // vt1-altura do chão
               t.Escala(E,ve);
               t.Translacao(T,vt);
               t.MxM(T,E,MT);
               O->Transforoma(MT);
               scene->Objetos.push_back(O);
               iobj++;

               //Janela1-piso predio esq
              //ve0 espessura do cubo, ve1 altura do cubo, ve2 comprimento dir
             // vt0 dist pra frente, vt1-altura do chão, vt2 - dist pra esq
               O = CuboUni3(Cubo2);
               ve[0]=1;ve[1]=5;ve[2]=5;
               vt[0]=78;vt[1]=40;vt[2]=13;
               t.Escala(E,ve);
               t.Translacao(T,vt);
               t.MxM(T,E,MT);
               O->Transforoma(MT);
               scene->Objetos.push_back(O);
               iobj++;

               //Janela2 piso predio esq
              //ve0 espessura do cubo, ve1 altura do cubo, ve2 comprimento dir
             // vt0 dist pra frente, vt1-altura do chão, vt2 - dist pra esq
               O = CuboUni3(Cubo2);
               ve[0]=1;ve[1]=5;ve[2]=5;
               vt[0]=78;vt[1]=40;vt[2]=20;
               t.Escala(E,ve);
               t.Translacao(T,vt);
               t.MxM(T,E,MT);
               O->Transforoma(MT);
               scene->Objetos.push_back(O);
               iobj++;

               //Janela3 piso predio esq
              //ve0 espessura do cubo, ve1 altura do cubo, ve2 comprimento dir
             // vt0 dist pra frente, vt1-altura do chão, vt2 - dist pra esq
               O = CuboUni3(Cubo2);
               ve[0]=1;ve[1]=5;ve[2]=5;
               vt[0]=78;vt[1]=40;vt[2]=42;
               t.Escala(E,ve);
               t.Translacao(T,vt);
               t.MxM(T,E,MT);
               O->Transforoma(MT);
               scene->Objetos.push_back(O);
               iobj++;

               //Janela4 piso predio esq
              //ve0 espessura do cubo, ve1 altura do cubo, ve2 comprimento dir
             // vt0 dist pra frente, vt1-altura do chão, vt2 - dist pra esq
               O = CuboUni3(Cubo2);
               ve[0]=1;ve[1]=5;ve[2]=5;
               vt[0]=78;vt[1]=40;vt[2]=49;
               t.Escala(E,ve);
               t.Translacao(T,vt);
               t.MxM(T,E,MT);
               O->Transforoma(MT);
               scene->Objetos.push_back(O);
               iobj++;
//-------------------------------------------------------------------------------------------------------------------
               //Portão central predio-1
              //ve0 espessura do cubo, ve1 altura do cubo, ve2 comprimento dir
             // vt0 dist pra frente, vt1-altura do chão, vt2 - dist pra esq
               O = CuboUni3(Cubo2);
               ve[0]=1;ve[1]=16;ve[2]=9;
               vt[0]=78;vt[1]=5;vt[2]=31;
               t.Escala(E,ve);
               t.Translacao(T,vt);
               t.MxM(T,E,MT);
               O->Transforoma(MT);
               scene->Objetos.push_back(O);
               iobj++;

               //janela1 res-chao predio-1
               //ve0 espessura do cubo, ve1 altura do cubo, ve2 comprimento dir
               // vt0 dist pra frente, vt1-altura do chão, vt2 - dist pra esq
               O = CuboUni3(Cubo2);
               ve[0]=1;ve[1]=5;ve[2]=5;
               vt[0]=78;vt[1]=16;vt[2]=15;
               t.Escala(E,ve);
               t.Translacao(T,vt);
               t.MxM(T,E,MT);
               O->Transforoma(MT);
               scene->Objetos.push_back(O);
               iobj++;

              //janela2 res-chao predio-1
              //ve0 espessura do cubo, ve1 altura do cubo, ve2 comprimento dir
              // vt0 dist pra frente, vt1-altura do chão, vt2 - dist pra esq
               O = CuboUni3(Cubo2);
               ve[0]=1;ve[1]=5;ve[2]=5;
               vt[0]=78;vt[1]=16;vt[2]=22;
               t.Escala(E,ve);
               t.Translacao(T,vt);
               t.MxM(T,E,MT);
               O->Transforoma(MT);
               scene->Objetos.push_back(O);
               iobj++;

               //janela3 res-chao predio esq
              //ve0 espessura do cubo, ve1 altura do cubo, ve2 comprimento dir
             // vt0 dist pra frente, vt1-altura do chão, vt2 - dist pra esq
               O = CuboUni3(Cubo2);
               ve[0]=1;ve[1]=5;ve[2]=5;
               vt[0]=78;vt[1]=16;vt[2]=44;
               t.Escala(E,ve);
               t.Translacao(T,vt);
               t.MxM(T,E,MT);
               O->Transforoma(MT);
               scene->Objetos.push_back(O);
               iobj++;

               //Janela4 res-chao predio-1
              //ve0 espessura do cubo, ve1 altura do cubo, ve2 comprimento dir
             // vt0 dist pra frente, vt1-altura do chão, vt2 - dist pra esq
               O = CuboUni3(Cubo2);
               ve[0]=1;ve[1]=5;ve[2]=5;
               vt[0]=78;vt[1]=16;vt[2]=51;
               t.Escala(E,ve);
               t.Translacao(T,vt);
               t.MxM(T,E,MT);
               O->Transforoma(MT);
               scene->Objetos.push_back(O);
               iobj++;
//----------------------------------------SINAL ESTRADA----------------------------------------------------------------

               //sinal-1 estrada
                //ve1 espessura do cubo, ve2 altura do cubo, ve2 comprimento dir
                O = CuboUni3(Cubo2);
                ve[0]=3;ve[1]=1;ve[2]=10;
                vt[0]=49;vt[1]=0;vt[2]=5;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

                //sinal1 pedestre
               //ve1 espessura do cubo, ve2 altura do cubo, ve2 comprimento dir
                 O = CuboUni3(Cubo2);
                 ve[0]=3;ve[1]=1;ve[2]=20;
                 vt[0]=57;vt[1]=0;vt[2]=22;
                 t.Escala(E,ve);
                 t.Translacao(T,vt);
                 t.MxM(T,E,MT);
                 O->Transforoma(MT);
                 scene->Objetos.push_back(O);
                 iobj++;

                 //sinal2 pedestre
                  O = CuboUni3(Cubo2);
                  ve[0]=3;ve[1]=1;ve[2]=20;
                  vt[0]=52;vt[1]=0;vt[2]=22;
                  t.Escala(E,ve);
                  t.Translacao(T,vt);
                  t.MxM(T,E,MT);
                  O->Transforoma(MT);
                  scene->Objetos.push_back(O);
                  iobj++;

                  //sinal3 pedestre
                   O = CuboUni3(Cubo2);
                   ve[0]=3;ve[1]=1;ve[2]=20;
                   vt[0]=47;vt[1]=0;vt[2]=22;
                   t.Escala(E,ve);
                   t.Translacao(T,vt);
                   t.MxM(T,E,MT);
                   O->Transforoma(MT);
                   scene->Objetos.push_back(O);
                   iobj++;

                   //sinal4 pedestre
                    O = CuboUni3(Cubo2);
                    ve[0]=3;ve[1]=1;ve[2]=20;
                    vt[0]=42;vt[1]=0;vt[2]=22;
                    t.Escala(E,ve);
                    t.Translacao(T,vt);
                    t.MxM(T,E,MT);
                    O->Transforoma(MT);
                    scene->Objetos.push_back(O);
                    iobj++;
//-------------------------------------------------------------------------------------------------------------------

               /* predio dir first
               O = CuboUni3(Cubo1); //ve0 espessura do cubo, ve1 altura do cubo, ve2 comprimento do cubo (dir)
               ve[0]=15;ve[1]=50;ve[2]=50;
               vt[0]=5;vt[1]=0;vt[2]=8; // vt0 dist pra frente, vt1-altura do chão, vt2 - dist pra esq
               t.Escala(E,ve);
               t.Translacao(T,vt);
               t.MxM(T,E,MT);
               O->Transforoma(MT);
               scene->Objetos.push_back(O);
               iobj++; */

               // predio-2
                    O = CuboUni3(Cubo1); //ve0 espessura do cubo, ve1 altura do cubo, ve2 comprimento do cubo (dir)
                    ve[0]=15;ve[1]=50;ve[2]=25;
                    vt[0]=3;vt[1]=0;vt[2]=8; // vt0 dist pra frente, vt1-altura do chão, vt2 - dist pra esq
                    t.Escala(E,ve);
                    t.Translacao(T,vt);
                    t.MxM(T,E,MT);
                    O->Transforoma(MT);
                    scene->Objetos.push_back(O);
                    iobj++;

                    // janela-1 lateral predio 2
                          O = CuboUni3(Cubo2);
                          ve[0]=5;ve[1]=5;ve[2]=2;
                          vt[0]=8;vt[1]=10;vt[2]=6;
                          t.Escala(E,ve);
                          t.Translacao(T,vt);
                          t.MxM(T,E,MT);
                          O->Transforoma(MT);
                          scene->Objetos.push_back(O);
                          iobj++;

                    // janela-2 lateral predio 2
                                O = CuboUni3(Cubo2);
                                ve[0]=5;ve[1]=5;ve[2]=2;
                                vt[0]=8;vt[1]=20;vt[2]=6;
                                t.Escala(E,ve);
                                t.Translacao(T,vt);
                                t.MxM(T,E,MT);
                                O->Transforoma(MT);
                                scene->Objetos.push_back(O);
                                iobj++;

                  // janela-3 lateral predio 2
                         O = CuboUni3(Cubo2);
                         ve[0]=5;ve[1]=5;ve[2]=2;
                         vt[0]=8;vt[1]=30;vt[2]=6;
                         t.Escala(E,ve);
                         t.Translacao(T,vt);
                         t.MxM(T,E,MT);
                         O->Transforoma(MT);
                         scene->Objetos.push_back(O);
                         iobj++;

                  // janela-3 lateral predio 2
                                O = CuboUni3(Cubo2);
                                ve[0]=5;ve[1]=5;ve[2]=2;
                                vt[0]=8;vt[1]=40;vt[2]=6;
                                t.Escala(E,ve);
                                t.Translacao(T,vt);
                                t.MxM(T,E,MT);
                                O->Transforoma(MT);
                                scene->Objetos.push_back(O);
                                iobj++;

//----------------------------MUROS-------------------------------------------------------------------------

                    // muro 1
                         O = CuboUni3(Cubo2);
                         ve[0]=20;ve[1]=20;ve[2]=2;
                         vt[0]=0;vt[1]=0;vt[2]=0;
                         t.Escala(E,ve);
                         t.Translacao(T,vt);
                         t.MxM(T,E,MT);
                         O->Transforoma(MT);
                         scene->Objetos.push_back(O);
                         iobj++;

                 // muro 2 (meio)
                       O = CuboUni3(Cubo2);
                       ve[0]=20;ve[1]=20;ve[2]=2;
                       vt[0]=1;vt[1]=0;vt[2]=45;
                       t.Escala(E,ve);
                       t.Translacao(T,vt);
                       t.MxM(T,E,MT);
                       O->Transforoma(MT);
                       scene->Objetos.push_back(O);
                       iobj++;





               /* Topo da construção dir
               O = CuboUni3(Cubo2);
               ve[0]=15;ve[1]=3;ve[2]=53;
               vt[0]=5;vt[1]=50.1;vt[2]=6;
               t.Escala(E,ve);
               t.Translacao(T,vt);
               t.MxM(T,E,MT);
               O->Transforoma(MT);
               scene->Objetos.push_back(O);
               iobj++;

               */

               //Muro trás (grande)
                O = CuboUni3(Cubo2);
                ve[0]=2;ve[1]=3;ve[2]=98;
                vt[0]=0;vt[1]=0;vt[2]=0;
                t.Escala(E,ve);
                t.Translacao(T,vt);
                t.MxM(T,E,MT);
                O->Transforoma(MT);
                scene->Objetos.push_back(O);
                iobj++;

                // muro 3
                     O = CuboUni3(Cubo2);
                     ve[0]=22;ve[1]=20;ve[2]=2;
                     vt[0]=0;vt[1]=0;vt[2]=98;
                     t.Escala(E,ve);
                     t.Translacao(T,vt);
                     t.MxM(T,E,MT);
                     O->Transforoma(MT);
                     scene->Objetos.push_back(O);
                     iobj++;

                 // ve0 espessura do cubo, ve1 altura do cubo, ve2 comprimento do cubo (dir)
                 // vt0 dist pra frente, vt1-altura do chão, vt2 - dist pra esq

                // predio-3
                   O = CuboUni3(Cubo1);
                   ve[0]=15;ve[1]=50;ve[2]=20;
                   vt[0]=3;vt[1]=0;vt[2]=60;
                   t.Escala(E,ve);
                   t.Translacao(T,vt);
                   t.MxM(T,E,MT);
                   O->Transforoma(MT);
                   scene->Objetos.push_back(O);
                   iobj++;

                   // janela-1 lateral predio 3
                         O = CuboUni3(Cubo2);
                         ve[0]=5;ve[1]=5;ve[2]=2;
                         vt[0]=8;vt[1]=10;vt[2]=58;
                         t.Escala(E,ve);
                         t.Translacao(T,vt);
                         t.MxM(T,E,MT);
                         O->Transforoma(MT);
                         scene->Objetos.push_back(O);
                         iobj++;

                   // janela-2 lateral predio 3
                               O = CuboUni3(Cubo2);
                               ve[0]=5;ve[1]=5;ve[2]=2;
                               vt[0]=8;vt[1]=20;vt[2]=58;
                               t.Escala(E,ve);
                               t.Translacao(T,vt);
                               t.MxM(T,E,MT);
                               O->Transforoma(MT);
                               scene->Objetos.push_back(O);
                               iobj++;

                 // janela-3 lateral predio 3
                        O = CuboUni3(Cubo2);
                        ve[0]=5;ve[1]=5;ve[2]=2;
                        vt[0]=8;vt[1]=30;vt[2]=58;
                        t.Escala(E,ve);
                        t.Translacao(T,vt);
                        t.MxM(T,E,MT);
                        O->Transforoma(MT);
                        scene->Objetos.push_back(O);
                        iobj++;

                 // janela-3 lateral predio 3
                               O = CuboUni3(Cubo2);
                               ve[0]=5;ve[1]=5;ve[2]=2;
                               vt[0]=8;vt[1]=40;vt[2]=58;
                               t.Escala(E,ve);
                               t.Translacao(T,vt);
                               t.MxM(T,E,MT);
                               O->Transforoma(MT);
                               scene->Objetos.push_back(O);
                               iobj++;

            }


}
void MainWindow::CamT(){

    Point Eye(Ex, Ey, Ez);
    Point LA(Lox,Loy,Loz);
    Point AVUp(Avx,Avy,Avz);

    Obs = new Observador(Eye,LA,AVUp);
    Cam = new Camera(W,H,-d,sizeX,sizeY);
    scene = new Cenario(Cam, Amb, Bg, Obs);

    scene->Renderiza_somb = this->Renderiza_sombras;

    RGB iF1(rF1,gF1,bF1); // Iluminação pontual


    pF1 = new Point(pF1x,pF1y,pF1z); // Posição da luz



    if(rF1!=0||gF1!=0||bF1!=0)
        scene->addFonte2(pF1,iF1);
}

void MainWindow::Sair(){
    free(Cubo1);
    free(Cubo2);
    free(Cubo3);
    free(Grama);
    free(Quadra);
    free(Bg);
    free(Amb);
    exit(0);

}
void MainWindow::Pad(){
    sizeX = 500;
    sizeY = 500;
    W = 0.5;
    H = 0.5;
    d = 1.5;
    rF1=0, rF2=0, rF3=0, rF4=0, rF5=0;
    gF1=0, gF2=0, gF3=0, gF4=0, gF5=0;
    bF1=0, bF2=0, bF3=0, bF4=0, bF5=0;

    Ex=250; Ey=200;Ez=-250;
    Lox=50; Loy=0;Loz=50;
    Avx=0; Avy=0; Avz=0;

    Amb->R=0.4;Amb->G=0.4;Amb->B=0.4;
    Bg->R=0.22;Bg->R=0.22;Bg->B=0.22;

}

//Pontos de Fuga

void MainWindow::RenderPFuga(Cenario *Cena){


    QImage image = QImage( 500, 500, QImage::Format_RGB32 );

    for( int i=0; i<400; i++) {

        float Yi= (Cena->Cam->h/2)-(Cena->Cam->DY/2)-(i*Cena->Cam->DY);
        for( int j=0; j<400; j++ ) {

            float Xj = (-Cena->Cam->w/2)+(Cena->Cam->DX/2)+(j*Cena->Cam->DX);
            Point Pij(Xj,Yi,Cena->Cam->d);
            Pij.normalize();
                Point Po(0,0,0);
                RGB* print = Cena->Ray_Pix_Ilm(Po, Pij);
                image.setPixel( j, i, qRgb(print->R*255, print->G*255, print->B*255));
        }
    }

    QGraphicsScene * graphic = new QGraphicsScene( this );
    graphic->addPixmap( QPixmap::fromImage( image ) );
    ui->graphicsModel->setScene(graphic);

    Cena->Libera();
    free(Cena);
}

void MainWindow::RenderPFuga2(Cenario *Cena){


    QImage image = QImage( 400, 400, QImage::Format_RGB32 );

    for( int i=0; i<400; i++) {

        float Yi= (Cena->Cam->h/2)-(Cena->Cam->DY/2)-(i*Cena->Cam->DY);
        for( int j=0; j<400; j++ ) {

            float Xj = (-Cena->Cam->w/2)+(Cena->Cam->DX/2)+(j*Cena->Cam->DX);
            Point Pij(Xj,Yi,Cena->Cam->d);
            Pij.normalize();
                Point Po(0,0,0);
                RGB* print = Cena->Ray_Pix_Ilm(Po, Pij);
                image.setPixel( j, i, qRgb(print->R*255, print->G*255, print->B*255));
        }
    }

    QGraphicsScene * graphic = new QGraphicsScene( this );
    graphic->addPixmap( QPixmap::fromImage( image ) );
    ui->graphicsModel_2->setScene(graphic);

    Cena->Libera();
    free(Cena);
}

void MainWindow::RenderPFuga3(Cenario *Cena){


    QImage image = QImage( 400, 400, QImage::Format_RGB32 );

    for( int i=0; i<400; i++) {

        float Yi= (Cena->Cam->h/2)-(Cena->Cam->DY/2)-(i*Cena->Cam->DY);
        for( int j=0; j<400; j++ ) {

            float Xj = (-Cena->Cam->w/2)+(Cena->Cam->DX/2)+(j*Cena->Cam->DX);
            Point Pij(Xj,Yi,Cena->Cam->d);
            Pij.normalize();
                Point Po(0,0,0);
                RGB* print = Cena->Ray_Pix_Ilm(Po, Pij);
                image.setPixel( j, i, qRgb(print->R*255, print->G*255, print->B*255));
        }
    }

    QGraphicsScene * graphic = new QGraphicsScene( this );
    graphic->addPixmap( QPixmap::fromImage( image ) );
    ui->graphicsModel_3->setScene(graphic);

    Cena->Libera();
    free(Cena);
}

void MainWindow::Fuga_1P(){

    Point Eye(-25, 5, 5);
    Point LA(5,5,5);
    Point AVUp(5,10,5);

    Obs = new Observador(Eye,LA,AVUp);
    Cam = new Camera(0.5,0.5,-1,400,400);
    RGB *Back = new RGB(0.1, 0.1, 0.1);
    RGB *iA = new RGB(0.7, 0.7, 0.7);
    Cenario *Cena = new Cenario(Cam, iA, Back, Obs);

    Objeto *cubo =  new Objeto();

    cubo->addPoint(0,0,0);
    cubo->addPoint(10,0,0);
    cubo->addPoint(0,10,0);
    cubo->addPoint(10,10,0);
    cubo->addPoint(0,0,10);
    cubo->addPoint(10,0,10);
    cubo->addPoint(0,10,10);
    cubo->addPoint(10,10,10);

    cubo->addFace(0,6,4,Cubo3);
    cubo->addFace(0,2,6,Cubo3);

    cubo->addFace(0,1,3,Cubo2);
    cubo->addFace(0,3,2,Cubo2);

    cubo->addFace(4,7,5,Cubo2);
    cubo->addFace(4,6,7,Cubo2);

    cubo->addFace(0,4,5,Cubo3);
    cubo->addFace(0,5,1,Cubo3);

    cubo->addFace(2,7,6,Cubo3);
    cubo->addFace(2,3,7,Cubo3);

    Cena->Objetos.push_back(cubo);
    Cena->Word_Cam();
    RenderPFuga(Cena);


}

void MainWindow::Fuga_2P(){

    Point Eye(5, 0.5, 5);
    Point LA(0.5,0.5,0.5);
    Point AVUp(0.5,10,0.5);

    Obs = new Observador(Eye,LA,AVUp);
    Cam = new Camera(0.5,0.5,-1,400,400);
    RGB *Back = new RGB(0.1, 0.1, 0.1);
    RGB *iA = new RGB(0.7, 0.7, 0.7);
    Cenario *Cena = new Cenario(Cam, iA, Back, Obs);
    Objeto *O;
    O = CuboUni3(Quadra);
    O->faces.at(2)->M=Cubo2;
    O->faces.at(3)->M=Cubo2;
    O->faces.at(4)->M=Cubo3;
    O->faces.at(5)->M=Cubo3;

    Cena->Objetos.push_back(O);
    Cena->Word_Cam();
    RenderPFuga2(Cena);
}

void MainWindow::Fuga_3P(){


    Point Eye(15, 10, 15);
    Point LA(0.5,0.5,0.5);
    Point AVUp(0.5,10,0.5);

    Obs = new Observador(Eye,LA,AVUp);
    Cam = new Camera(0.5,0.5,-3,400,400);
    RGB *Back = new RGB(0.1, 0.1, 0.1);
    RGB *iA = new RGB(0.7, 0.7, 0.7);
    Cenario *Cena = new Cenario(Cam, iA, Back,Obs);
    Objeto *O;
    O = CuboUni3(Quadra);

    O->faces.at(2)->M=Cubo2;
    O->faces.at(3)->M=Cubo2;
    O->faces.at(4)->M=Cubo3;
    O->faces.at(5)->M=Cubo3;

    Cena->Objetos.push_back(O);
    Cena->Word_Cam();
    RenderPFuga3(Cena);


}

void MainWindow::sombras_rend(bool s){
  Renderiza_sombras = s;
}

void MainWindow::setTeta(double T){
    Teta=T;
}

void MainWindow::setFator(double F){
    FOb = F;
}

void MainWindow::setPF1x(double d){
    pF1x=d;
}
void MainWindow::setPF1y(double d){
    pF1y=d;
}
void MainWindow::setPF1z(double d){
    pF1z=d;
}
void MainWindow::setF1r(int x){
    rF1 = (float)x/255;
}
void MainWindow::setF1g(int x){
    gF1 = (float)x/255;
}
void MainWindow::setF1b(int x){
    bF1 = (float)x/255;
}

void MainWindow::setPF2x(double d){
    pF2x=d;
}
void MainWindow::setPF2y(double d){
    pF2y=d;
}
void MainWindow::setPF2z(double d){
    pF2z=d;
}
void MainWindow::setF2r(int x){
    rF2 = (float)x/255;
}
void MainWindow::setF2g(int x){
    gF2 = (float)x/255;
}
void MainWindow::setF2b(int x){
    bF2 = (float)x/255;
}

void MainWindow::setPF3x(double d){
    pF3x=d;
}
void MainWindow::setPF3y(double d){
    pF3y=d;
}
void MainWindow::setPF3z(double d){
    pF3z=d;
}
void MainWindow::setF3r(int x){
    rF3 = (float)x/255;
}
void MainWindow::setF3g(int x){
    gF3 = (float)x/255;
}
void MainWindow::setF3b(int x){
    bF3 = (float)x/255;
}


void MainWindow::setPF4x(double d){
    pF4x=d;
}
void MainWindow::setPF4y(double d){
    pF4y=d;
}
void MainWindow::setPF4z(double d){
    pF4z=d;
}
void MainWindow::setF4r(int x){
    rF4 = (float)x/255;
}
void MainWindow::setF4g(int x){
    gF4 = (float)x/255;
}
void MainWindow::setF4b(int x){
    bF4 = (float)x/255;
}


void MainWindow::setPF5x(double d){
    pF5x=d;
}
void MainWindow::setPF5y(double d){
    pF5y=d;
}
void MainWindow::setPF5z(double d){
    pF5z=d;
}
void MainWindow::setF5r(int x){
    rF5 = (float)x/255;
}
void MainWindow::setF5g(int x){
    gF5 = (float)x/255;
}
void MainWindow::setF5b(int x){
    bF5 = (float)x/255;
}



void MainWindow::setBG_R(int I){
    Bg->R=(float)I/255;
}
void MainWindow::setBG_G(int I){
    Bg->G=(float)I/255;
}
void MainWindow::setBG_B(int I){
    Bg->B=(float)I/255;
}

void MainWindow::IA_R(int I){
    Amb->R= (float)I/255;
}
void MainWindow::IA_G(int I){
    Amb->G= (float)I/255;
}
void MainWindow::IA_B(int I){
    Amb->B= (float)I/255;
}

void MainWindow::set_rSp1(int I){
    rSp1 = (float)I/255;
}
void MainWindow::set_gSp1(int I){
    gSp1 = (float)I/255;
}
void MainWindow::set_bSp1(int I){
    bSp1 = (float)I/255;
}
void MainWindow::set_rSp2(int I){
    rSp2 = (float)I/255;
}
void MainWindow::set_gSp2(int I){
    gSp2 = (float)I/255;
}
void MainWindow::set_bSp2(int I){
    bSp2 = (float)I/255;
}
void MainWindow::set_rSp3(int I){
    rSp3 = (float)I/255;
}
void MainWindow::set_gSp3(int I){
    gSp3 = (float)I/255;
}
void MainWindow::set_bSp3(int I){
    bSp3 = (float)I/255;
}
void MainWindow::set_rSp4(int I){
    rSp4 = (float)I/255;
}
void MainWindow::set_gSp4(int I){
    gSp4 = (float)I/255;
}
void MainWindow::set_bSp4(int I){
    bSp4 = (float)I/255;
}

void MainWindow::setGrama(bool b){
    grama=b;
}
void MainWindow::setQuadra(bool b){
    quadra=b;
}
void MainWindow::setCubos(bool b){
    cubos=b;
}

void MainWindow::setTraves(bool b){
    traves=b;
}
void MainWindow::setP1(bool b){
    p1=b;
}
void MainWindow::setP2(bool b){
    p2=b;
}
void MainWindow::setP3(bool b){
    p3=b;
}
void MainWindow::setP4(bool b){
    p4=b;
}

void MainWindow::Eye_X(double x){
    Ex=(float)x;
}
void MainWindow::Eye_Y(double x){
    Ey=(float)x;
}
void MainWindow::Eye_Z(double x){
    Ez=(float)x;
}

void MainWindow::Lo_X(double x){
    Lox=(float)x;
}
void MainWindow::Lo_Y(double x){
    Loy=(float)x;
}
void MainWindow::Lo_Z(double x){
    Loz=(float)x;
}

void MainWindow::Av_X(double x){
    Avx=(float)x;
}
void MainWindow::Av_Y(double x){
    Avy=(float)x;
}
void MainWindow::Av_Z(double x){
    Avz=(float)x;
}

void MainWindow::setW(double x){
    W=(float)x;
}
void MainWindow::setH(double x){
    H=(float)x;
}
void MainWindow::setD(double x){
    d=(float)x;
}
void MainWindow::setSX(double x){
    sizeX=(float)x;
}
void MainWindow::setSY(double x){
    sizeY=(float)x;
}


Objeto* MainWindow::CuboUni3(Material *M){
    Objeto *cubo = new Objeto();

    cubo->addPoint(0,0,0);
    cubo->addPoint(1,0,0);
    cubo->addPoint(0,1,0);
    cubo->addPoint(1,1,0);
    cubo->addPoint(0,0,1);
    cubo->addPoint(1,0,1);
    cubo->addPoint(0,1,1);
    cubo->addPoint(1,1,1);

    cubo->addFace(0,3,1,M);
    cubo->addFace(0,2,3,M);
    cubo->addFace(1,7,5,M);
    cubo->addFace(1,3,7,M);
    cubo->addFace(4,5,7,M);
    cubo->addFace(4,7,6,M);
    cubo->addFace(0,4,6,M);
    cubo->addFace(0,6,2,M);
    cubo->addFace(0,5,4,M);
    cubo->addFace(0,1,5,M);
    cubo->addFace(2,6,7,M);
    cubo->addFace(2,7,3,M);

   return cubo;
}


/* if(traves){
      //Trave 1 (BASE)
      O = CuboUni3(Trave);
      ve[0]=0.5;ve[1]=12;ve[2]=0.5;
      vt[0]=40;vt[1]=0.8;vt[2]=9;
      t.Escala(E,ve);
      t.Translacao(T,vt);
      t.MxM(T,E,MT);
      O->Transforoma(MT);
      scene->Objetos.push_back(O);
      iobj++;

      //Trave 1 (BASE)
      O = CuboUni3(Trave);
      ve[0]=0.5;ve[1]=12;ve[2]=0.5;
      vt[0]= 55;vt[1]=0.8;vt[2]=9;
      t.Escala(E,ve);
      t.Translacao(T,vt);
      t.MxM(T,E,MT);
      O->Transforoma(MT);
      scene->Objetos.push_back(O);
      iobj++;

      //Trave 1 (TOPO)
      O = CuboUni3(Trave);
      ve[0]= 15;ve[1]=0.5;ve[2]=0.5;
      vt[0]= 40;vt[1]=12;vt[2]=9;
      t.Escala(E,ve);
      t.Translacao(T,vt);
      t.MxM(T,E,MT);
      O->Transforoma(MT);
      scene->Objetos.push_back(O);
      iobj++;

      //Trave 2 (BASE)
      O = CuboUni3(Trave);
      ve[0]=0.5;ve[1]=12;ve[2]=0.5;
      vt[0]= 55;vt[1]=0.8;vt[2]=78;
      t.Escala(E,ve);
      t.Translacao(T,vt);
      t.MxM(T,E,MT);
      O->Transforoma(MT);
      scene->Objetos.push_back(O);
      iobj++;

      //Trave 2 (BASE)
      O = CuboUni3(Trave);
      ve[0]=0.5;ve[1]=12;ve[2]=0.5;
      vt[0]= 40;vt[1]=0.8;vt[2]=78;
      t.Escala(E,ve);
      t.Translacao(T,vt);
      t.MxM(T,E,MT);
      O->Transforoma(MT);
      scene->Objetos.push_back(O);
      iobj++;

      //Trave 2 (TOPO)
      O = CuboUni3(Trave);
      ve[0]= 15;ve[1]=0.5;ve[2]=0.5;
      vt[0]= 40;vt[1]=12;vt[2]=78;
      t.Escala(E,ve);
      t.Translacao(T,vt);
      t.MxM(T,E,MT);
      O->Transforoma(MT);
      scene->Objetos.push_back(O);
      iobj++;
} */
