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

    particle = new(Particle);

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
    particle->x += particle->speed * particle->angX;
    particle->y += particle->speed * particle->angY;
    particle->z += particle->speed * particle->angZ;

    glColor3f(1, 0.6, 0);
    glPushMatrix();
        glTranslatef(x+particle->x, y+particle->y, zoom+particle->z);
        glRotatef(angle, 1, 1, 1);
        glutSolidSphere(1.0, 50, 50);
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
    posX1 = e->x()-(x*50);
    posY1 = e->y()+(y*50);
}

void GLWidget::mouseMoveEvent(QMouseEvent *e){
    x = (float)(posX1 - e->x())/-50;
    y = (float)(posY1 - e->y())/50;
}


void GLWidget::wheelEvent(QWheelEvent *e){
    int numDegrees = e->delta() / 8;
    int numSteps = numDegrees / 15;

    scrollVertically(numSteps);

    e->accept();
}
