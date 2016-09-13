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

    particle[0] = new(Particle);
    particle[1] = new(Particle);
    particle[1]->speed = 0.0;
    particle[1]->mass = 100;

    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

void GLWidget::initializeGL(){
    glClearColor(0.2, 0.2, 0.2, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int i = 0; i < NUM_P; i++)
    {
        particle[i]->x += particle[i]->speed * particle[i]->angX;
        particle[i]->y += particle[i]->speed * particle[i]->angY;
        if(particle[i]->mass == 1)
            glColor3f(1, 0.6, 0);
        if(particle[i]->mass == 100)
            glColor3f(0, 0, 0.6);
        glPushMatrix();
            glTranslatef(x+particle[i]->x, y+particle[i]->y, zoom+particle[i]->z);
            //glRotatef(angle, 1, 1, 1);
            glutSolidSphere(1.0, 10, 5);
        glPopMatrix();
    }
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
