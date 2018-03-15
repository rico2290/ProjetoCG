#-------------------------------------------------
#
# Project created by QtCreator 2018-01-07T10:50:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrabalhoFinalCG
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -fopenmp

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    esfera.cpp \
    rgb.cpp \
    material.cpp \
    aresta.cpp \
    face.cpp \
    operacoes.cpp \
    luz.cpp \
    observador.cpp \
    objeto.cpp \
    camera.cpp \
    cenario.cpp \
    v3.cpp \
    spot.cpp \
    transformacoes.cpp

HEADERS += \
        mainwindow.h \
    esfera.h \
    rgb.h \
    material.h \
    aresta.h \
    face.h \
    operacoes.h \
    luz.h \
    observador.h \
    objeto.h \
    camera.h \
    cenario.h \
    v3.h \
    spot.h \
    transformacoes.h

FORMS += \
        mainwindow.ui

DISTFILES +=
