#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel * mylabel = new QLabel("my label text", this);
    mylabel->setGeometry(10,10,200,30);

}

MainWindow::~MainWindow()
{
    delete ui;
}
