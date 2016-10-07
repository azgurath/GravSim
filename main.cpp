/**
  * @file main.cpp
  * @author Andrew Hoover
  * @date 9/17/2016
  * @brief Main function to create the window.
  *
  * Contains function to create and display the main window.
  */

#include "mainwindow.h"
#include <QApplication>
#include <GL/glu.h>

/**
 * Main function, creates and displays the main window.
 *
 * @brief qMain
 * @param argc amount of command line arguments
 * @param argv command line arguments
 * @return success or error code
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
