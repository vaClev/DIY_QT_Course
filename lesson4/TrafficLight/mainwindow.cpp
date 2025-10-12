#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "trafficlight.h"
#include <QLabel>
#include <QPushButton>

//Конструктор
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_trafficLight = new TrafficLight(this);
    m_statusLabel = new QLabel("Светофор выключен", this);
    m_statusLabel->setGeometry(10,10,200,30);

    InitConnectSlots();
}

//Деструктор
MainWindow::~MainWindow()
{
    delete ui;
}

//Слоты главного окна - которые подключены к сигналам "рабочего" бизнесс-класса.
void MainWindow::OnRedLight()
{
    m_statusLabel->setText("🔴 КРАСНЫЙ - СТОП!");
    m_statusLabel->setStyleSheet("color: red; font-weight: bold;");
}

void MainWindow::OnYellowLight()
{
    m_statusLabel->setText("🟡 ЖЕЛТЫЙ - ВНИМАНИЕ!");
    m_statusLabel->setStyleSheet("color: orange; font-weight: bold;");
}

void MainWindow::OnGreenLight()
{
    m_statusLabel->setText("🟢 ЗЕЛЕНЫЙ - ИДИТЕ!");
    m_statusLabel->setStyleSheet("color: green; font-weight: bold;");
}

void MainWindow::OnLightChanged(const QString &color, int duration)
{
    qDebug() << "Color:" << color << "duration:" << duration/1000 << "seconds";
    // Можно добавить логику, например, запись в файл или отправку по сети
}



//Подключение к слотов к сигналам клaсса TrafficLight
void MainWindow::InitConnectSlots()
{
    // Соединяем пользовательские сигналы со слотами
    connect(m_trafficLight, &TrafficLight::RedLightOn,
            this,           &MainWindow::OnRedLight);

    connect(m_trafficLight, &TrafficLight::YellowLightOn,
            this,           &MainWindow::OnYellowLight);

    connect(m_trafficLight, &TrafficLight::GreenLightOn,
            this,           &MainWindow::OnGreenLight);

    connect(m_trafficLight, &TrafficLight::LightChanged,
            this,           &MainWindow::OnLightChanged);


    // Добавляем кнопки управления
    QPushButton *startBtn = new QPushButton("Старт", this);
    startBtn->setGeometry(10,50,200,30);
    QPushButton *stopBtn  = new QPushButton("Стоп", this);
    stopBtn->setGeometry(10,100,200,30);

    //Подключаем кнопки управления
    connect(startBtn,       &QPushButton::clicked,
            m_trafficLight, &TrafficLight::Start);
    connect(stopBtn,        &QPushButton::clicked,
            m_trafficLight, &TrafficLight::Stop);
}
