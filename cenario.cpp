#include "cenario.h"
#define PI 3.14159265
Cenario::Cenario()
{

}

Cenario::Cenario(Camera *_Cam, RGB*_Amb, RGB *_BG, Observador* _Obs){
    this->Obs=_Obs;
    this->Cam=_Cam;
    this->Amb=_Amb;
    this->BG=_BG;
    this->Renderiza_somb=false;
}
void Cenario::addObjeto(Objeto *O){
    this->Objetos.push_back(O);
}
void Cenario::addFonte(luz *L){
    this->fontes_luminosas.push_back(L);
}
void Cenario::addSpot(Spot *S){
    this->fontes_spot.push_back(S);
}
void Cenario::addFonte2(Point *P, RGB I){
    luz* L = new luz(I,P);
    this->fontes_luminosas.push_back(L);
}

void Cenario::addSpot2(Point *P, Point*D, RGB I, float A){
    luz* L = new luz(I,P);
    Spot* Sp = new Spot(L,D,A);
    this->fontes_spot.push_back(Sp);
}

void Cenario::Word_Cam(){
    transformacoes t;
    float WC[4][4];
    this->Obs->Word_Cam(WC);

    for(std::vector<Objeto*>::iterator i = this->Objetos.begin(); i!= this->Objetos.end(); i++){
        //(*i)->points.at(0)->ImpPoint();
        (*i)->Transforoma(WC);
        //(*i)->points.at(0)->ImpPoint();
        for(std::vector<Face*>::iterator f = (*i)->faces.begin(); f!=(*i)->faces.end();f++){
                (*f)->atNormal();
            }

    }
    for(std::vector<luz*>::iterator i = this->fontes_luminosas.begin();i!= this->fontes_luminosas.end();i++){
        t.MxV(WC,(*i)->P);

    }

    for(std::vector<Spot*>::iterator i = this->fontes_spot.begin();i!=this->fontes_spot.end();i++){
        t.MxV(WC,(*i)->Luz->P);
    }
    Point *p = &Obs->Pos;
    t.MxV(WC,p);

}
float Cenario::Ray_intersept(Point Po, Point D, int &Obj, int &Face){

    float Tint=999;
    int iFace, iObj;
    int cont=0;
    for(std::vector<Objeto*>::iterator i=this->Objetos.begin();i!=Objetos.end();i++){
        int iFace_temp;
        float temp = (*i)->Ray_intersept(Po, D, &iFace_temp);//Inter(Pij,&iFace_temp);
        if(temp != -1 && temp<Tint){
            Tint=temp;
            iFace=iFace_temp;
            iObj=cont;
        }
        cont++;

    }
    if(Tint != 999){
        Face = iFace;
        Obj = iObj;
    }else
        Tint = -1;

    return Tint;

}
RGB* Cenario::Ray_Pix_Ilm(Point Po, Point D){
    RGB* RayPix = new RGB(this->BG->R, this->BG->G, this->BG->B); //Inicializa com background color;

    int iObj,iFace;

    float t = this->Ray_intersept(Po, D, iObj,iFace);

    if(t!=-1 && t>0){
        Face* F = this->Objetos.at(iObj)->faces.at(iFace);
        Point Pint = D;
        Pint.normalize();
        Pint.operator *=(t);

        Point nFace = F->N;
        nFace.normalize();

        RGB A(F->M->A.R*this->Amb->R,F->M->A.G*this->Amb->G,F->M->A.B*this->Amb->B);

        float Dr=0, Dg=0, Db=0, Er=0, Eg=0, Eb=0;
        luz* Luz;
        for(std::vector<luz*>::iterator i=this->fontes_luminosas.begin();i!=fontes_luminosas.end();i++){

            Luz = (*i);
            Point Fonte = (*Luz->P);
            Fonte.operator -=(Pint);
            Fonte.normalize();

            bool sombra_rend = false;
            if(Renderiza_somb){
                sombra_rend = this->sombra(Pint, Fonte);
            }

            if(!sombra_rend){


                float xDif = nFace.ProdutoEscalar(Fonte);

                Point v = Po;//Luz->P;
                v.operator -=(Pint);
                v.normalize();
                Point r = nFace;
                r.operator *=(2*xDif);
                r.operator -=(Fonte);
                r.normalize();
                float xEsp=v.ProdutoEscalar(r);
                xEsp=pow(xEsp,F->M->m);

                if(xDif > 0){
                    Dr += Luz->F.R*xDif;
                    Dg += Luz->F.G*xDif;
                    Db += Luz->F.B*xDif;
                }
                if(xEsp > 0){
                    Er += Luz->F.R*xEsp;
                    Eg += Luz->F.G*xEsp;
                    Eb += Luz->F.B*xEsp;
                }
            }
        }

        for(std::vector<Spot*>::iterator i=this->fontes_spot.begin();i!=fontes_spot.end();i++){

            Luz = (*i)->Luz;
            Point Fonte = (*Luz->P);
            Fonte.operator -=(Pint);
            Fonte.normalize();

            Point *D = (*i)->Direcao;
            D->x = -D->x; D->y = -D->y; D->z = -D->z;
            float cosDL = Fonte.ProdutoEscalar(*D);


                if(cosDL>0){

                    float cosTeta = cos(((*i)->Abertura*PI/180));

                    if(cosTeta<cosDL){

                    bool sombra_rend = false;

                    if(Renderiza_somb){

                        sombra_rend = this->sombra(Pint, Fonte);
                    }

                    if(!sombra_rend){
                    //float Teta = acos (cos) * 180.0 / PI;


                        float R = Luz->F.R*cosDL;
                        float G = Luz->F.G*cosDL;
                        float B = Luz->F.B*cosDL;

                        float xDif = nFace.ProdutoEscalar(Fonte);

                        Point v = Po;
                        v.operator -=(Pint);
                        v.normalize();
                        Point r = nFace;
                        r.operator *=(2*xDif);
                        r.operator -=(Fonte);
                        r.normalize();
                        float xEsp=v.ProdutoEscalar(r);
                        xEsp=pow(xEsp,F->M->m);

                        if(xDif > 0){
                            Dr += R*xDif;
                            Dg += G*xDif;
                            Db += B*xDif;
                        }
                        if(xEsp > 0){
                            Er += R*xEsp;
                            Eg += G*xEsp;
                            Eb += B*xEsp;
                        }
                    }
                }

        }


        }

        RGB D(F->M->D.R*(Dr),F->M->D.G*(Dg),F->M->D.B*(Db));
        RGB E(F->M->E.R*(Er),F->M->E.G*(Eg),F->M->E.B*(Eb));

        RayPix->R = A.R + D.R + E.R;
        RayPix->G = A.G + D.G + E.G;
        RayPix->B = A.B + D.B + E.B;
        RayPix->Normalize();

    }

    return RayPix;
}

RGB* Cenario::Ilm_Pint(Point Pint, Point nFace, Material *MF){
    RGB* RayPix = new RGB(this->BG->R, this->BG->G, this->BG->B); //Inicializa com background color;
    RGB A(MF->A.R*this->Amb->R,MF->A.G*this->Amb->G,MF->A.B*this->Amb->B);

    float Dr=0, Dg=0, Db=0, Er=0, Eg=0, Eb=0;

        for(std::vector<luz*>::iterator i=this->fontes_luminosas.begin();i!=fontes_luminosas.end();i++){

            luz* Luz = (*i);
            Point Fonte = (*Luz->P);
            Fonte.operator -=(Pint);
            Fonte.normalize();
            //Fonte.ImpPoint();
            float xDif = nFace.ProdutoEscalar(Fonte);
            //std::cout<< "\nXDif" << xDif;

            Point v = this->Obs->Pos;
            v.operator -=(Pint);
            v.normalize();
            Point r = nFace;
            r.operator *=(2*xDif);
            r.operator -=(Fonte);
            r.normalize();
            float xEsp=v.ProdutoEscalar(r);
            xEsp=pow(xEsp,MF->m);
            //std::cout << "\nXEsp" << xEsp;
            if(xDif > 0){
                Dr += Luz->F.R*xDif;
                Dg += Luz->F.G*xDif;
                Db += Luz->F.B*xDif;
            }
            if(xEsp > 0){
                Er += Luz->F.R*xEsp;
                Eg += Luz->F.G*xEsp;
                Eb += Luz->F.B*xEsp;
            }
        }

        //std::cout << "\n Dr: " << Dr<< ", Dg: " << Dg << ", Db: " << Db;
        for(std::vector<Spot*>::iterator i=this->fontes_spot.begin();i!=fontes_spot.end();i++){

            luz* Luz = (*i)->Luz;
            Point Fonte = (*Luz->P);
            Fonte.operator -=(Pint);
            Fonte.normalize();

            Point *D = (*i)->Direcao;
            D->x = -D->x; D->y = -D->y; D->z = -D->z;
            float cos = Fonte.ProdutoEscalar(*D);

            if(cos>0){
                float Teta = acos (cos) * 180.0 / PI;
                std::cout << "Teta: " << Teta;
                if(Teta < (*i)->Abertura){

                    float R = Luz->F.R*cos;
                    float G = Luz->F.G*cos;
                    float B = Luz->F.B*cos;

                    float xDif = nFace.ProdutoEscalar(Fonte);

                    Point v = this->Obs->Pos;  //Luz->P;
                    v.operator -=(Pint);
                    v.normalize();
                    Point r = nFace;
                    r.operator *=(2*xDif);
                    r.operator -=(Fonte);
                    r.normalize();
                    float xEsp=v.ProdutoEscalar(r);
                    xEsp=pow(xEsp,MF->m);

                    if(xDif > 0){
                        Dr += R*xDif;
                        Dg += G*xDif;
                        Db += B*xDif;
                    }
                    if(xEsp > 0){
                        Er += R*xEsp;
                        Eg += G*xEsp;
                        Eb += B*xEsp;
                    }
                }


            }

        }
        //std::cout << "\n Dr: " << Dr<< ", Dg: " << Dg << ", Db: " << Db;

        RGB D(MF->D.R*(Dr),MF->D.G*(Dg),MF->D.B*(Db));
        RGB E(MF->E.R*(Er),MF->E.G*(Eg),MF->E.B*(Eb));


        RayPix->R = A.R + D.R + E.R;
        RayPix->G = A.G + D.G + E.G;
        RayPix->B = A.B + D.B + E.B;
        //RayPix->Normalize();

        std::cout <<"\nIluminacao Amb: " << A.R << ", " << A.G <<", " << A.B<< ";";
        std::cout <<"\nIluminacao Dif: " << D.R << ", " << D.G <<", " << D.B << ";";
        std::cout <<"\nIluminacao Esp: " << E.R << ", " << E.G <<", " << E.B<< ";";


    return RayPix;

}
void Cenario::CuboUni(){
    Objeto *cubo = new Objeto();

    cubo->addPoint(0,0,1);
    cubo->addPoint(1,0,1);
    cubo->addPoint(1,0,0);
    cubo->addPoint(0,0,0);
    cubo->addPoint(0,1,1);
    cubo->addPoint(1,1,1);
    cubo->addPoint(1,1,0);
    cubo->addPoint(0,1,0);

    cubo->addFace2(0,3,1);
    cubo->addFace2(1,3,2);
    cubo->addFace2(4,0,1);
    cubo->addFace2(1,5,4);
    cubo->addFace2(5,1,2);
    cubo->addFace2(2,6,5);
    cubo->addFace2(6,2,3);
    cubo->addFace2(3,7,6);
    cubo->addFace2(3,0,4);
    cubo->addFace2(4,7,3);
    cubo->addFace2(4,5,7);
    cubo->addFace2(5,6,7);

    this->addObjeto(cubo);
}

void Cenario::CuboUni2(Material *M1,Material *M2,Material *M3,
                       Material *M4,Material *M5,Material *M6) {
    Objeto *cubo = new Objeto();

    cubo->addPoint(0,0,1);
    cubo->addPoint(1,0,1);
    cubo->addPoint(1,0,0);
    cubo->addPoint(0,0,0);
    cubo->addPoint(0,1,1);
    cubo->addPoint(1,1,1);
    cubo->addPoint(1,1,0);
    cubo->addPoint(0,1,0);

    cubo->addFace(0,3,1,M1);
    cubo->addFace(1,3,2,M1);
    cubo->addFace(4,0,1,M2);
    cubo->addFace(1,5,4,M2);
    cubo->addFace(5,1,2,M3);
    cubo->addFace(2,6,5,M3);
    cubo->addFace(6,2,3,M4);
    cubo->addFace(3,7,6,M4);
    cubo->addFace(3,0,4,M5);
    cubo->addFace(4,7,3,M5);
    cubo->addFace(4,5,7,M6);
    cubo->addFace(5,6,7,M6);

    this->addObjeto(cubo);


}
void Cenario::CuboUni3(Material *M){
    Objeto *cubo = new Objeto();
    //Objeto *C = new Objeto();

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

    this->addObjeto(cubo);

}


bool Cenario::sombra(Point Pint, Point l){
    bool Sombra = false;
    for(std::vector<Objeto*>::iterator i=this->Objetos.begin();
        i!=Objetos.end() && !Sombra;i++){
        Sombra = (*i)->Obstaculo(Pint, l);
    }
    return Sombra;
}


void Cenario::Libera(){

    for(std::vector<Objeto*>::iterator i=this->Objetos.begin();
        i!=Objetos.end();i++){
        (*i)->Libera();
        free(*i);
    }
    Objetos.clear();

    for(std::vector<luz*>::iterator i=this->fontes_luminosas.begin();
        i!=fontes_luminosas.end();i++){
        free((*i)->P);
        free(*i);
    }
    fontes_luminosas.clear();
    free(Obs);
    free(Cam);

}
