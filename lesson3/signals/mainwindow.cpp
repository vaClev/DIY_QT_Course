#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProgressBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //Старый синтаксис connect.
    //connect(ui->pushButton, SIGNAL(clicked()),
    //        this,           SLOT(onButtonClicked()));

    //Новый синтаксис connect
    connect(ui->pushButton, &QPushButton::clicked,
            this,           &MainWindow::onButtonClicked);

    InitSliderProgress();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Наш первый слот!
void MainWindow::onButtonClicked()
{
    qDebug()<<"Button pushed - congratulation!"; //Выводит сообщение в консоль "Вывод приложения"
    //std::cout<<"this is std::cout message"<<std::endl; // для оконных приложений не понимает куда выводить

    if(m_slider != nullptr)
      m_slider->setValue(50);
}


//Примерчик: Сигнал и слот с одним аргументом
void MainWindow::InitSliderProgress()
{
    m_slider = new QSlider(Qt::Horizontal, this);
    QProgressBar * progressBar = new QProgressBar(this);

    //координаты для примера
    m_slider->setGeometry(50,50,200,30);
    progressBar->setGeometry(50,100,200,30);

    //диапазоны для примера
    m_slider->setRange(0,100);
    progressBar->setRange(0,100);

    //соединяем сигнал и слот
    connect(m_slider,    &QSlider::valueChanged,
            progressBar, &QProgressBar::setValue);

}
