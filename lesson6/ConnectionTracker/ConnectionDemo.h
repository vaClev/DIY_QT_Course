#ifndef CONNECTIONDEMO_H
#define CONNECTIONDEMO_H

#include <QWidget>
class QPushButton;
class QTextEdit;

class ConnectionDemo : public QWidget
{
    Q_OBJECT

private:
    QPushButton * m_directBtn;
    QPushButton * m_queuedBtn;
    QPushButton * m_blockingBtn;
    QPushButton * m_uniqueBtn;
    QTextEdit * m_logText;
    int m_callCount{0};

public:
    explicit ConnectionDemo(QWidget *parent = nullptr);

public slots:
    void onDirectConnection();
    void onQueuedConnection();
    void OnBlockingConnection();
    void OnUniqueConnection();

private slots:
    void WorkerSlot(int value);
    void LogMessage(const QString& message);

private:
    void setupUI();
    void setupConnections();
};

#endif // CONNECTIONDEMO_H
