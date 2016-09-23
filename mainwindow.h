#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
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
