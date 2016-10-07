/**
  * @file mainwindow.h
  * @author Andrew Hoover
  * @date 9/20/2016
  * @brief MainWindow class. Has methods to handle toolbar input.
  *
  * MainWindow class decleration, includes methods to create and destroy the
  * main window using Qt functions, and methods to handle user interaction
  * with the toolbar.
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/**
 * MainWindow class decleration, includes methods to create and destroy the
 * main window using Qt functions, and methods to handle user interaction
 * with the toolbar.
 *
 * @brief The MainWindow class
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // functions for handling toolbar button presses.
    void on_action_Exit_triggered();

    void on_actionRestart_triggered();

    void on_action_Gravity_triggered();

    void on_action_Pause_triggered();

    void on_action1_triggered();

    void on_action2_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
