/**
  * @file glwidget.cpp
  * @author Andrew Hoover
  * @date 9/28/2016
  * @brief Draws the graphics, handles mouse and keyboard input.
  *
  * Implmentation of the glwidget class. Inherits from GLWidget to
  * be a widget on the main window of the program. It draws graphics
  * using OpenGL on the widget.
  */

#include "glwidget.h"
#include "gravity.h"
#include <GL/glu.h>
#include <QDebug>

extern bool CONTINUE;
extern bool RESTART;
extern bool PRESET;

/**
 * Constructor. Initialized the pan and zoom amount, creates
 * gravity object to hold the universe, and sets the update
 * function to be called 60 times a second.
 *
 * @brief GLWidget::GLWidget
 * @param parent
 */

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus); // make the widget register clicks.
    // Set zoom and pan variables to defaults
    zoom = 1.0;
    angleX = 0.0;
    angleY = 0.0;
    x = 0;
    y = 0;
    posX1 = 0;
    posY1 = 0;

    gravity = new Gravity(PRESET); // Create the universe.

    // Make the scene draw a new frame every 16 miliseconds.
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);
}

/**
 * Initialize the OpenGL settings for the background color
 * and lighting.
 *
 * @brief GLWidget::initializeGL
 */

void GLWidget::initializeGL(){
    // Set background color
    glClearColor(0.2, 0.2, 0.2, 1);
    // Set lighting
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

}

/**
 * Draw the scene. Called automatically by the timer function,
 * it first updates the location of the particles and then displays
 * them.
 *
 * @brief GLWidget::paintGL
 */

void GLWidget::paintGL(){
    // If RESTART was pressed, create a new universe and reset the pan
    // and zoom amounts.
    if(RESTART)
    {
        delete gravity;
        gravity = new Gravity(PRESET);
        RESTART = false;
        CONTINUE = false;
        zoom = 1.0;
        x = 0;
        y = 0;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update the universe if not paused
    if(CONTINUE)
        gravity->update();

    // Walk through every particle and draw it
    for(int i = 0; i < gravity->partNum(); i++)
    {
        // Transform the scene according to the pan and zoom amounts
        glPushMatrix();
        glRotatef(angleY, 0, 1, 0);
        glRotatef(angleX, 1, 0, 0);
        // Set the color based on the mass of the particle
        if(gravity->color(i) == 1)
            glColor3f(1, 0, 0);
        if(gravity->color(i) < 0.2)
            glColor3f(0, 1, 0);
        if(gravity->color(i) < 0.02)
            glColor3f(0, 0, 1);

        // Push another matrix and tranform to the location of the particle.
        // Draw a cube around it of length 1.
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

/**
 * Automatically called when the window is resized. Updates the
 * perspective and viewport of the environment.
 *
 * @brief GLWidget::resizeGL
 * @param w width of the window.
 * @param h height of the window.
 */

void GLWidget::resizeGL(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.5, (float)w/h, 1, 10000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);
}

/**
 * Increase or decrease the zoom amount based on the
 * amount the scroll wheel callback function registered.
 *
 * @brief GLWidget::scrollVertically
 * @param numSteps amount the wheel was scrolled.
 */

void GLWidget::scrollVertically(int numSteps)
{
    zoom += (float)numSteps*3;
}

/**
 * Callback function called when a mouse press is
 * detected in the window. If the button is the right
 * button, the location of the click is saved in order
 * to update the pan amount when the mouse is dragged.
 *
 * @brief GLWidget::mousePressEvent
 * @param e mouse event
 */

void GLWidget::mousePressEvent(QMouseEvent *e){
    // If right button clicked
    if(e->button() == Qt::RightButton)
    {
        // Save location of click
        posX1 = e->x()-(x*10);
        posY1 = e->y()+(y*10);
    }
}

/**
 * Callback function called when the mouse is moved while
 * at least one button is being held. If it's the right button,
 * compare the current location to the saved location of the click
 * and update the pan variables accordingly.
 *
 * @brief GLWidget::mouseMoveEvent
 * @param e mouse event.
 */

void GLWidget::mouseMoveEvent(QMouseEvent *e){
    // If right button
    if(e->buttons() == Qt::RightButton)
    {
        // Update pan
        x = (float)(posX1 - e->x())/-10;
        y = (float)(posY1 - e->y())/10;
    }
}

/**
 * Callback function for keyboard input. Updates the angle
 * rotation of the scene if an arrow key is pressed.
 *
 * @brief GLWidget::keyPressEvent
 * @param e keyboard event
 */

void GLWidget::keyPressEvent(QKeyEvent *e){
    // Update X and Y angle is arrow key pressed.
    if(e->key() == Qt::Key_Up)
        angleX += 2;
    if(e->key() == Qt::Key_Down)
        angleX -= 2;

    if(e->key() == Qt::Key_Left)
        angleY -= 2;
    if(e->key() == Qt::Key_Right)
        angleY += 2;
}

/**
 * Callback function for the mouse wheel. Used to update
 * the zoom on the scene when the wheel is scrolled.
 *
 * @brief GLWidget::wheelEvent
 * @param e wheel event
 */

void GLWidget::wheelEvent(QWheelEvent *e){
    // Update zoom.
    int numDegrees = e->delta() / 8;
    int numSteps = numDegrees / 15;

    scrollVertically(numSteps);

    e->accept();
}
