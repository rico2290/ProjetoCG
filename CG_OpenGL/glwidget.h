#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>

class GLWidget : public QGLWidget
{
    Q_OBJECT
    QTimer* timer;
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    float Ex=-150, Ey=150, Ez=-150;
    float Lox=50, Loy=0, Loz=50;
    float Avx=50, Avy=100, Avz=50;
    bool Luzes = false;


signals:

public slots:
    void LuzesProj(bool);
    void Eye_X(double);
    void Eye_Y(double);
    void Eye_Z(double);
    void Lo_X(double);
    void Lo_Y(double);
    void Lo_Z(double);
    void Av_X(double);
    void Av_Y(double);
    void Av_Z(double);

};

#endif // GLWIDGET_H
