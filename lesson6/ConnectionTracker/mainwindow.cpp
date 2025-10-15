#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ConnectionDemo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ConnectionDemo * connectionDemo = new ConnectionDemo(this);

    //размещаем в интерфейсе
    setCentralWidget(connectionDemo);
}

MainWindow::~MainWindow()
{
    delete ui;
}
