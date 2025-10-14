#ifndef MESSAGEHISTORY_H
#define MESSAGEHISTORY_H

#include <QWidget>
class QListWidget;

class MessageHistory : public QWidget
{
    Q_OBJECT
    QListWidget * m_historyList;

public:
    explicit MessageHistory(QWidget *parent = nullptr);


public slots:
    void OnMessageReceived(const QString & type, const QString &message, const QDateTime & timestamp);

};

#endif // MESSAGEHISTORY_H
