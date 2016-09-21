#include "glwidget.h"
#include "gravity.h"
#include <GL/glu.h>
#include <QDebug>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    zoom = 1.0;
    angleX = 0.0;
    angleY = 0.0;
    xPan = 0.0;
    yPan = 0.0;
    x = 0;
    y = 0;
    posX1 = 0;
    posY1 = 0;

    gravity = new(Gravity);

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
        gravity->update();
        glPushMatrix();
        glRotatef(angleY, 0, 1, 0);
        glRotatef(angleX, 1, 0, 0);
        if(gravity->color(i) > 0.1)
            glColor3f(1.0*gravity->color(i), 0, 0);
        else
            if(gravity->color(i) > 0.001)
                glColor3f(0, 100*gravity->color(i), 0);
            else
                glColor3f(0, 0, 10000*gravity->color(i));

        glPushMatrix();
            glTranslatef(x+gravity->x(i), y+gravity->y(i), zoom+gravity->z(i));
            glBegin(GL_POLYGON);
                glVertex3f( -0.5, -0.5, -0.5);
                glVertex3f( -0.5, 0.5, -0.5);
                glVertex3f( 0.5, 0.5, -0.5);
                glVertex3f( 0.5, -0.5, -0.5); //back face
            glEnd();
            glBegin(GL_POLYGON);
                glVertex3f( -0.5, -0.5, 0.5);
                glVertex3f( -0.5, 0.5, 0.5);
                glVertex3f( 0.5, 0.5, 0.5);
                glVertex3f( 0.5, -0.5, 0.5); //front gace
            glEnd();
            glBegin(GL_POLYGON);
                glVertex3f( -0.5, -0.5, -0.5);
                glVertex3f( -0.5, 0.5, -0.5);
                glVertex3f( -0.5, 0.5, 0.5);
                glVertex3f( -0.5, -0.5, 0.5); //left face
            glEnd();
            glBegin(GL_POLYGON);
                glVertex3f( 0.5, 0.5, -0.5);
                glVertex3f( 0.5, -0.5, -0.5);
                glVertex3f( 0.5, -0.5, 0.5);
                glVertex3f( 0.5, 0.5, 0.5); //right face
            glEnd();
            glBegin(GL_POLYGON);
                glVertex3f( -0.5, 0.5, -0.5);
                glVertex3f( 0.5, 0.5, -0.5);
                glVertex3f( 0.5, 0.5, 0.5);
                glVertex3f( -0.5, 0.5, 0.5); //top face
                glEnd();
            glBegin(GL_POLYGON);
                glVertex3f( -0.5, -0.5, -0.5);
                glVertex3f( 0.5, -0.5, -0.5);
                glVertex3f( 0.5, -0.5, 0.5);
                glVertex3f( -0.5, -0.5, 0.5); //bottom face
            glEnd();
        glPopMatrix();
        glPopMatrix();
    }
}

void GLWidget::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.5, (float)w/h, 1, 10000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);
}

void GLWidget::scrollVertically(int numSteps)
{
    zoom += (float)numSteps*3;
}

void GLWidget::mousePressEvent(QMouseEvent *e){
    if(e->button() == Qt::RightButton)
    {
        posX1 = e->x()-(x*10);
        posY1 = e->y()+(y*10);
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *e){
    if(e->buttons() == Qt::RightButton)
    {
        x = (float)(posX1 - e->x())/-10;
        y = (float)(posY1 - e->y())/10;
    }
}

void GLWidget::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Up)
        angleX += 2;
    if(e->key() == Qt::Key_Down)
        angleX -= 2;

    if(e->key() == Qt::Key_Left)
        angleY -= 2;
    if(e->key() == Qt::Key_Right)
        angleY += 2;
}



void GLWidget::wheelEvent(QWheelEvent *e){
    int numDegrees = e->delta() / 8;
    int numSteps = numDegrees / 15;

    scrollVertically(numSteps);

    e->accept();
}
