#include "glwidget.h"
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>

void TriangularPrism(){


    glBegin(GL_TRIANGLES);
    glVertex3f(1, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(1, 0, 0);
    glVertex3f(1,1,0.5);
    glVertex3f(1,0,1);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(1,1,0.5);
    glVertex3f(0,0,1);
    glVertex3f(1,0,1);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(0,0,1);
    glVertex3f(0,1,0.5);
    glVertex3f(0,0,0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(1,0,0);
    glVertex3f(0,1,0.5);
    glVertex3f(1,1,0.5);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(1,0,1);
    glVertex3f(0,0,1);
    glVertex3f(0,0,0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(1,1,0.5);
    glVertex3f(0,1,0.5);
    glVertex3f(0,0,1);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0.5);
    glEnd();

}


GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer->start(0);
}

void GLWidget::initializeGL()
{
       GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
       GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};
       GLfloat luzEspecular[4]={0.7, 0.7, 0.7, 1.0};
       GLfloat posicaoLuz[4]={20.0, 30.0, 0.0, 1.0};

       GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
       GLint especMaterial = 60;

       glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

       // Habilita o modelo de colorização de Gouraud
       glShadeModel(GL_SMOOTH);

       // Define a refletância do material
       glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
       // Define a concentração do brilho
       glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

       // Ativa o uso da luz ambiente
       glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

       // Define os parâmetros da luz de número 0
       glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
       glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
       glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
       glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

       // Habilita a definição da cor do material a partir da cor corrente
      // glEnable(GL_COLOR_MATERIAL);
       //Habilita o uso de iluminação
       glEnable(GL_LIGHTING);

       // Habilita a luz de número 0

        //glEnable(GL_LIGHT0);



       // Habilita o depth-buffering  Opacidade dos objetos
       glEnable(GL_DEPTH_TEST);




}

void GLWidget::paintGL()
{

    float asfalto[4]={0.3235, 0.3823, 0.4450, 1.0};
    float grama[4]={0.4196, 0.5568, 0.1372, 1.0};

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode(GL_MODELVIEW);



    glMaterialfv(GL_FRONT, GL_AMBIENT, grama);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, grama);
    glMaterialfv(GL_FRONT, GL_SPECULAR, grama);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100.0);

    glLoadIdentity();
    glScalef(100,0.8,95);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);



    //Pistas
   //glColor3f(0.3235, 0.3823, 0.4450);


    glMaterialfv(GL_FRONT, GL_AMBIENT,asfalto);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,asfalto);
    glMaterialfv(GL_FRONT, GL_SPECULAR, asfalto);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100.0);

    glLoadIdentity();
    glTranslatef(45,0.8,0);
    glScalef(10,0.2,55);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glTranslatef(0,0.8,55);
    glScalef(100,0.2,10);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glTranslatef(55,0.8,25);
    glScalef(30,0.2,5);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glTranslatef(30,0.8,28);
    glScalef(15,0.2,4);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

   // glColor3f(205/255,184/255,180/255);

    float pista2[4]={205/255,184/255,180/255, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, pista2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pista2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, pista2);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100.0);

    float vx[4] ={7, 27, 55,85};
    for(int i=0; i<4; i++){
        float Ez = 6;
        if(i==1)
            Ez=11;
        glLoadIdentity();
        glTranslatef(vx[i],0.8,65);
        glScalef(4,0.1,Ez);
        glTranslatef(0.5,0.5,0.5);
        glutSolidCube(1);
    }


    //Casas

    float Casa1[4]={0.1843f, 0.3098f, 0.3098f, 1.0};
    float Casa2[4]={0.8235f, 0.4118f, 0.1176f, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, Casa1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Casa1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Casa1);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100.0);

    glLoadIdentity();
    glTranslatef(70,0.8,5);
    glScalef(20,2.5,20);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);


    glMaterialfv(GL_FRONT, GL_AMBIENT, Casa2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Casa2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Casa2);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100.0);

    glLoadIdentity();
    glTranslatef(70,0.8,30);
    glScalef(20,2.5,20);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    float Casa3[4]={0.8235f, 0.7059f, 0.5490f, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, Casa3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Casa3);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Casa3);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100.0);

    glLoadIdentity();
    glTranslatef(75,0.8,70);
    glScalef(20,2.5,20);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    float Casa4[4]={0.4120f, 0.2529f, 0.8039f, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, Casa4);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Casa4);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Casa4);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100.0);

    glLoadIdentity();
    glTranslatef(50,0.8,70);
    glScalef(20,20,20);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    float Casa5[4]={0.9569, 0.6431, 0.3765, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, Casa5);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Casa5);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Casa5);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100.0);

    glLoadIdentity();
   // glColor3f(0.9569, 0.6431, 0.3765);
    glTranslatef(21,0.8,75);
    glScalef(15,3,15);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glTranslatef(2,0.8,70);
    glScalef(20,20,20);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    float Casa6[4]={0.9608f, 0.9608f, 0.8627f, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, Casa6);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Casa6);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Casa6);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100);

    glLoadIdentity();
    //glColor3f(0.9608f, 0.9608f, 0.8627f);
    glTranslatef(5,0.8,20);
    glScalef(25,3,20);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glTranslatef(5,0.8,6);
    glScalef(15,3,15);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);


    //Telhados

    float Telha1[4]={0.9608f, 0.9608f, 0.8627f, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, Telha1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Telha1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Telha1);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100);

    glLoadIdentity();
    //glColor3f(0.9608f, 0.9608f, 0.8627f);
    glTranslatef(70,3.3,5);
    glScalef(20,2,20);
    TriangularPrism();

    float Telha2[4]={72/255,118/255, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, Telha2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Telha2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Telha2);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100);

    glLoadIdentity();
    glColor3f(72/255,118/255,1);
    glTranslatef(70,3.3,30);
    glScalef(20,2,20);
    TriangularPrism();

    glLoadIdentity();
    //glColor3f(72/255,118/255,1);
    glTranslatef(21,3.8,75);
    glScalef(15,2,15);
    TriangularPrism();

    glLoadIdentity();
    glTranslatef(2,20.8,70);
    glScalef(20,3,20);
    TriangularPrism();

    float Telha3[4]={0.1843f, 0.3098f, 0.3098f, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, Telha3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Telha3);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Telha3);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100);

    glLoadIdentity();
   //glColor3f(0.1843f, 0.3098f, 0.3098f);
    glTranslatef(75,3.3,70);
    glScalef(20,2,20);
    TriangularPrism();

    glLoadIdentity();
    glTranslatef(50,20.7,70);
    glScalef(20,3,20);
    TriangularPrism();

    glLoadIdentity();
    glTranslatef(5,3.8,20);
    glScalef(25,3,20);
    TriangularPrism();

    glLoadIdentity();
    glTranslatef(5,3.8,6);
    glScalef(15,3,15);
    TriangularPrism();

    //Postes

    float Postes[4]={0.22,0.22,0.22, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, Postes);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Postes);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Postes);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100);

    glLoadIdentity();
    //glColor3f(0.22,0.22,0.22);
    glTranslatef(43,0.8,25);
    glScalef(0.5,15,0.5);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glColor3f(0.22,0.22,0.22);
    glTranslatef(43,15.8,25);
    glScalef(2.5,0.5,0.5);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glColor3f(0.22,0.22,0.22);
    glTranslatef(61,0.8,35);
    glScalef(0.5,15,0.5);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glColor3f(0.22,0.22,0.22);
    glTranslatef(59,15.8,35);
    glScalef(2.5,0.5,0.5);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);


    glLoadIdentity();
    glColor3f(0.22,0.22,0.22);
    glTranslatef(43,0.8,70);
    glScalef(0.5,15,0.5);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glColor3f(0.22,0.22,0.22);
    glTranslatef(43,15.8,68);
    glScalef(0.5,0.5,2.5);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glColor3f(0.22,0.22,0.22);
    glTranslatef(72,0.8,70);
    glScalef(0.5,15,0.5);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glColor3f(0.22,0.22,0.22);
    glTranslatef(72,15.8,68);
    glScalef(0.5,0.5,2.5);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    //Arvores

    float Arvs[4]={0.22,0.8,0.22, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, Arvs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Arvs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Arvs);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100);

    float z[4] = {8,14,40,60};
    for(int i=0; i<3; i++){
        for(int j=0; j<4;j++){
            glLoadIdentity();
            //glColor3f(0.22,0.8,0.22);
            glTranslatef(z[j],0.8,(i*5)+42);
            glScalef(1.5,7,1.5);
            glTranslatef(0.5,0.5,0.5);
            glutSolidCube(1);

        }
        glLoadIdentity();
        glTranslatef(72,0.8,(i*5)+75);
        glScalef(1.5,7,1.5);
        glTranslatef(0.5,0.5,0.5);
        glutSolidCube(1);

        glLoadIdentity();
        glTranslatef(40,0.8,(i*5)+75);
        glScalef(1.5,2,1.5);
        glTranslatef(0.5,0.5,0.5);
        glutSolidCube(1);

        for(int j=0; j<2;j++){
            glLoadIdentity();
            glTranslatef((j*20)+40,0.8,(i*5)+5);
            glScalef(1.5,2,1.5);
            glTranslatef(0.5,0.5,0.5);
            glutSolidCube(1);

            glLoadIdentity();
            glTranslatef(z[j],0.8,(i*5)+42);
            glScalef(1.5,2,1.5);
            glTranslatef(0.5,0.5,0.5);
            glutSolidCube(1);
        }



    }


    float Portas[4]={0.22,0.22,0.22, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, Portas);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Portas);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Portas);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100);

    //Portas

    glColor3f(0.9569, 0.6431, 0.3765);

    glLoadIdentity();
    glTranslatef(80,0.8,25);
    glScalef(1,2,0.1);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glTranslatef(80,0.8,29.8);
    glScalef(1,2,0.1);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glTranslatef(85,0.8,69.8);
    glScalef(1,2,0.1);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glTranslatef(55,0.8,69.8);
    glScalef(4,2.5,0.1);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glTranslatef(27,0.8,74.8);
    glScalef(3,2,0.1);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glTranslatef(7,0.8,69.8);
    glScalef(4,2.5,0.1);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);

    glLoadIdentity();
    glTranslatef(30,0.8,30);
    glScalef(0.1,2,1.5);
    glTranslatef(0.5,0.5,0.5);
    glutSolidCube(1);


//Janelas
    float Jan[4]={0.92,0.92,0.92, 1.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, Jan);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, Jan);
    glMaterialfv(GL_FRONT, GL_SPECULAR, Jan);
    glMaterialf  (GL_FRONT, GL_SHININESS, 100);;

    for(int i=0; i<3;i++){
        for(int j=0; j<4;j++){
            glLoadIdentity();
            glTranslatef((i*5)+6,(j*3)+6.8,69.8);
            glScalef(2,2,0.1);
            glTranslatef(0.5,0.5,0.5);
            glutSolidCube(1);

            glLoadIdentity();
            glTranslatef(70,(j*3)+6.8,(i*5)+72);
            glScalef(0.1,2,1);
            glTranslatef(0.5,0.5,0.5);
            glutSolidCube(1);

        }
        glLoadIdentity();
        glTranslatef(90,1.8,(i*5)+10);
        glScalef(0.1,1,1);
        glTranslatef(0.5,0.5,0.5);
        glutSolidCube(1);

        glLoadIdentity();
        glTranslatef(90,1.8,(i*5)+35);
        glScalef(0.1,1,1);
        glTranslatef(0.5,0.5,0.5);
        glutSolidCube(1);

        glLoadIdentity();
        glTranslatef(95,1.8,(i*5)+75);
        glScalef(0.1,1,1);
        glTranslatef(0.5,0.5,0.5);
        glutSolidCube(1);

        glLoadIdentity();
        glTranslatef((i*5)+6,1.8,5.9);
        glScalef(2,2,0.1);
        glTranslatef(0.5,0.5,0.5);
        glutSolidCube(1);

    }

}


void GLWidget::resizeGL(int w, int h)
{
    if(Luzes){
        glEnable(GL_LIGHT0);
    }else{
        glDisable(GL_LIGHT0);
    }

    glViewport(0,0, w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w/h, 1, 1000.0);
    // glFrustum(-100,-100,w,h,3,3000);
    gluLookAt(Ex,Ey,Ez,Lox,Loy,Loz,Avx,Avy,Avz);

    updateGL();
}

void GLWidget::LuzesProj(bool L){
    Luzes = L;
}

void GLWidget::Eye_X(double x){
    Ex=(float)x;
    updateGL();
}
void GLWidget::Eye_Y(double x){
    Ey=(float)x;
}
void GLWidget::Eye_Z(double x){
    Ez=(float)x;
}

void GLWidget::Lo_X(double x){
    Lox=(float)x;
}
void GLWidget::Lo_Y(double x){
    Loy=(float)x;
}
void GLWidget::Lo_Z(double x){
    Loz=(float)x;
}

void GLWidget::Av_X(double x){
    Avx=(float)x;
}
void GLWidget::Av_Y(double x){
    Avy=(float)x;
}
void GLWidget::Av_Z(double x){
    Avz=(float)x;
}

