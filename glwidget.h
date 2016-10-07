/**
  * @file glwidget.h
  * @author Andrew Hoover
  * @date 9/28/2016
  * @brief GLWidget class. Methods for drawing the scene and handling
  * user mouse and keyboard input.
  *
  * The GLWidget class inherits from  QWidget to be a widget on the main
  * application window. It has methods to draw the scene, and implement
  * mouse, scroll wheel and keyboard callback functions to handle user
  * input not related to the toolbar.
  */

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include "particle.h"
#include "gravity.h"

/**
 * The GLWidget class inherits from  QWidget to be a widget on the main
 * application window. It has methods to draw the scene, and implement
 * mouse, scroll wheel and keyboard callback functions to handle user
 * input not related to the toolbar.
 *
 * @brief The GLWidget class
 */

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL(); // Set the parameters for OpenGL
    void paintGL(); // Draw the scene, called every frame
    void resizeGL(int w, int h); // Called when the window is resized

    void scrollVertically(int numSteps); // Change zoom amount.

    // Callbacks for mouse and keyboard input
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void keyPressEvent(QKeyEvent *e);

    QTimer timer; // Used to call the paintGL function 60 times a second.
    int posX1, posY1; // Store location of right mouse click.
    float x, y; // Pan in x and y direction.
    float zoom; // Zoom amount.
    float angleX, angleY; // Angle of viewing.

    Gravity *gravity; // Gravity class to hold particles and update methods.
};

#endif // GLWIDGET_H
