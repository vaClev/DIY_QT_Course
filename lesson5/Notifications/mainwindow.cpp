#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "NotificationSystem.h"
#include "StatusBarLogger.h"
#include "MessageHistory.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    StatusBarLogger * statusLogger = new StatusBarLogger(this);
    MessageHistory * messageHistory = new MessageHistory(this);

    //размещаем в интерфейсе
    statusBar()->addWidget(statusLogger);
    setCentralWidget(messageHistory);
    centralWidget()->adjustSize();

    // Получаем ссылку на систему уведомлений
    NotificationSystem & notifier = NotificationSystem::Instance();

    //Множественные соединения
    connect(&notifier,    &NotificationSystem::InfoMessage,
            statusLogger, &StatusBarLogger::OnInfoMessage);
    connect(&notifier,    &NotificationSystem::WarningMessage,
            statusLogger, &StatusBarLogger::OnWarningMessage);
    connect(&notifier,    &NotificationSystem::ErrorMessage,
            statusLogger, &StatusBarLogger::OnErrorMessage);

    connect(&notifier,    &NotificationSystem::MessageReceived,
            messageHistory, &MessageHistory::OnMessageReceived);

    SetupTestButtons();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetupTestButtons()
{
    QWidget *buttonWidget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(buttonWidget);

    QPushButton *infoBtn = new QPushButton("Info", this);
    QPushButton *warningBtn = new QPushButton("Warning", this);
    QPushButton *errorBtn = new QPushButton("Error", this);

    layout->addWidget(infoBtn);
    layout->addWidget(warningBtn);
    layout->addWidget(errorBtn);

    // Создаем панель инструментов
    QToolBar *toolBar = new QToolBar("Main ToolBar", this);
    // Добавляем виджет с кнопками в тулбар
    toolBar->addWidget(buttonWidget);
    // Добавляем панель в главное окно
    addToolBar(toolBar);


    //Соединяем кнопки с системой уведомлений
    NotificationSystem & notifier = NotificationSystem::Instance();

    connect(infoBtn, &QPushButton::clicked, [&notifier]() {
        notifier.SendInfo("This is info");
    });

    connect(warningBtn, &QPushButton::clicked, [&notifier]() {
        notifier.SendWarning("Attencion! It is Warning!");
    });

    connect(errorBtn, &QPushButton::clicked, [&notifier]() {
        notifier.SendError("ERROR! WFT is going on?!");
    });
}
