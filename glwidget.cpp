#include "glwidget.h"
#include <GL/glut.h>
#include <QDebug>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    zoom = 1.0;
    angle = 0.0;
    xPan = 0.0;
    yPan = 0.0;
    x = 0;
    y = 0;
    posX1 = 0;
    posY1 = 0;
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void GLWidget::initializeGL(){
    glClearColor(0.2, 0.2, 0.2, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    angle += 0.5;

    glColor3f(1, 0.6, 0);
    glPushMatrix();
        glTranslatef(x, y, zoom);
        glRotatef(angle, 1, 1, 1);
        glutSolidTeapot(1);
    glPopMatrix();
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
}

void GLWidget::scrollVertically(int numSteps)
{
    zoom += (float)numSteps;
}

void GLWidget::mousePressEvent(QMouseEvent *e){
    posX1 = e->x();
    posY1 = e->y();
    qDebug() << posX1 << "," << posY1 << endl;
}

void GLWidget::mouseMoveEvent(QMouseEvent *e){
    x = posX1 - e->x();
    x *= -1;
    y = posY1 - e->y();
    x /= 100;
    y /= 100;
    qDebug() << x << "," << y << endl;
}


void GLWidget::wheelEvent(QWheelEvent *e){
    int numDegrees = e->delta() / 8;
    int numSteps = numDegrees / 15;

    scrollVertically(numSteps);

    e->accept();
}
