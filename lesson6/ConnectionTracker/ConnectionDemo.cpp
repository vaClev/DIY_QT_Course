#include "ConnectionDemo.h"

#include <QPushButton>
#include <QTextEdit>
#include <QThread>
#include <QVBoxLayout>
#include <QDateTime>

#include "ConnectionTracker.h"

ConnectionDemo::ConnectionDemo(QWidget *parent)
    : QWidget{parent}
{
    setupUI();
    setupConnections();
}

void ConnectionDemo::OnDirectConnection()
{
    LogMessage("Direct Connection: Start now");
    WorkerSlot(++m_callCount);//выполняется в текущем потоке

    //исполнение продолжается после выхода из WorkerSlot
    LogMessage("Direct Connection: End");
}

void ConnectionDemo::OnQueuedConnection()
{
    LogMessage("Queued Connection: Plan to event loop");
    //вызов метода в другом потоке
    QMetaObject::invokeMethod(this, "WorkerSlot", Qt::QueuedConnection, Q_ARG(int, ++m_callCount));
    LogMessage("Queued Connection: Request send");
}

void ConnectionDemo::OnBlockingConnection()
{
    LogMessage("Blocking Connection: start (block call)");

    // Создаем временный поток для демонстрации
    QThread * workerThread = new QThread();
    connect(workerThread, &QThread::started,
            [this, workerThread]()
            {
                QThread::msleep(10); // Имитация долгой операции
                QMetaObject::invokeMethod(this, "WorkerSlot", Qt::BlockingQueuedConnection, Q_ARG(int, ++m_callCount));
                workerThread->quit();
            }
            );

    workerThread->start();
    workerThread->wait(); // Блокируем основной поток. Дожидаемся окончания работы

    LogMessage("Blocking Connection: End");
    workerThread->deleteLater();

    //TODO : изучить deadlock состояние
}

void ConnectionDemo::OnUniqueConnection()
{
    static bool firstCall = true;
    if (firstCall) {
        LogMessage("Unique Connection: First call - connection set"); //Первый вызов - соединение установлено
        firstCall = false;
    } else {
        LogMessage("Unique Connection: All Next calls ignore"); //Последующие вызовы игнорируются
    }
}


//private slots
void ConnectionDemo::WorkerSlot(int value)
{
    QString msg = QString("Worker Slot: solve value %1 in thread %2")
                      .arg(value)
                      .arg((quintptr)QThread::currentThreadId());
    LogMessage(msg);
    QThread::msleep(500); // Имитация работы (любимое дело)
}

void ConnectionDemo::LogMessage(const QString &message)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    m_logText->append(QString("[%1] %2").arg(timestamp).arg(message));
}
//private slots end



// private methods
void ConnectionDemo::setupUI()
{
    m_directBtn = new QPushButton("Direct Connection", this);
    m_queuedBtn = new QPushButton("Queued Connection", this);
    m_blockingBtn = new QPushButton("Blocking Connection", this);
    m_uniqueBtn = new QPushButton("Unique Connection", this);
    m_logText = new QTextEdit(this);

    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->addWidget(m_directBtn);
    layout->addWidget(m_queuedBtn);
    layout->addWidget(m_blockingBtn);
    layout->addWidget(m_uniqueBtn);
    layout->addWidget(m_logText);
}

void ConnectionDemo::setupConnections()
{
    // Direct Connection - выполняется немедленно
    connect(m_directBtn, &QPushButton::clicked,
            this,        &ConnectionDemo::OnDirectConnection, Qt::DirectConnection);

    // Queued Connection - выполняется через event loop
    connect(m_queuedBtn, &QPushButton::clicked,
            this,        &ConnectionDemo::OnQueuedConnection, Qt::QueuedConnection);

    // Blocking Queued Connection (осторожно!)
    connect(m_blockingBtn, &QPushButton::clicked,
            this,          &ConnectionDemo::OnBlockingConnection, Qt::BlockingQueuedConnection);

    // Unique Connection - гарантирует одно соединение
    connect(m_uniqueBtn, &QPushButton::clicked,
            this,        &ConnectionDemo::OnUniqueConnection, Qt::UniqueConnection);
}
// private methods end
