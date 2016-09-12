#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>

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

    QTimer timer;
    int x, y, posX1, posY1;
    float zoom, angle, xPan, yPan;
};

#endif // GLWIDGET_H
