#-------------------------------------------------
#
# Project created by QtCreator 2016-09-11T17:05:43
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GravSim
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    particle.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    particle.h

FORMS    += mainwindow.ui

LIBS += -lglut -lGLU
