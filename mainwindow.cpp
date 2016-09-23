#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Exit_triggered()
{
    this->close();
}

void MainWindow::on_actionRestart_triggered()
{
    RESTART = true;
}

void MainWindow::on_action_Gravity_triggered()
{
    bool ok;
    GRAVITY_CONST = QInputDialog::getDouble(this, tr("Gravity"),
                                          tr("Strength of gravity:"),
                                          GRAVITY_CONST, 0, 1, 2, &ok);
}

void MainWindow::on_action_Pause_triggered()
{
    CONTINUE = !CONTINUE;
}

void MainWindow::on_action1_triggered()
{
    PRESET = 1;
    RESTART = true;
}

void MainWindow::on_action2_triggered()
{
    PRESET = 2;
    RESTART = true;
}
