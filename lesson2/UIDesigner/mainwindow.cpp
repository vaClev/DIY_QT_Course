#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CreateSomeUIElems();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Создание и наполнение меню
void MainWindow::CreateSomeUIElems()
{
    // создаем обект текстовая метка
    QLabel * myLabel = new QLabel("Привет, Qt я создан кодом!", this); // Ключевой момент: 'this'
    //расположим его по координатам 10, 50
    myLabel->setGeometry(10, 50, 200, 30); // (x, y, width, height)
}

//Действие при нажатии меню "файл" - "открыть"
void MainWindow::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                 QString::fromUtf8("Открыть файл"),
                                 QDir::currentPath(),
                                 "Images (*.png *.xpm *.jpg);;All files (*.*)");
    if(fileName.isEmpty())
    {
        QMessageBox::critical(this, "ошибка", "Файл не выбран!");
    }
    else
    {
        auto message = QString("Выбран файл %1, но пока не реализовано его открытие").arg(fileName);
        QMessageBox::information(this, "Заглушка", message);;
    }
    //далее следует обработать результат диалога
}

