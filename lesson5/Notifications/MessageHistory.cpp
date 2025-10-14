#include "MessageHistory.h"
#include <QListWidget>
#include <QDateTime>
#include <qboxlayout.h>
MessageHistory::MessageHistory(QWidget *parent)
    : QWidget{parent}
{
    m_historyList = new QListWidget(this);
    m_historyList->adjustSize();

    // Создаем layout для размещения
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(m_historyList);
}


void MessageHistory::OnMessageReceived(const QString &type, const QString &message, const QDateTime &timestamp)
{
    QString storyItem = QString("%1 : %2 : %3").arg(timestamp.toString(), type, message);

    if(m_historyList)
        m_historyList->addItem(storyItem);
}
