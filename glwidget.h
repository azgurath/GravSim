#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include "particle.h"
#include "gravity.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void scrollVertically(int numSteps);

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

    void keyPressEvent(QKeyEvent *e);

    QTimer timer;
    int posX1, posY1;
    float x, y, zoom, angleX, angleY, xPan, yPan;

    Gravity *gravity;
};

#endif // GLWIDGET_H
