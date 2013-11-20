#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "joystickconfigwidget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(&temp);

}

MainWindow::~MainWindow()
{
    this->setCentralWidget(NULL);
    delete ui;
}
