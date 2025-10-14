#ifndef NOTIFICATIONSYSTEM_H
#define NOTIFICATIONSYSTEM_H

#include <QObject>

class NotificationSystem : public QObject
{
    Q_OBJECT

private:
    //Приватный конструктор для Singletone
    explicit NotificationSystem(QObject *parent = nullptr);

public:
    static NotificationSystem& Instance();

signals:
    void InfoMessage(const QString & message);
    void WarningMessage(const QString & message);
    void ErrorMessage(const QString & message);
    void MessageReceived(const QString & type, const QString &message, const QDateTime & timestamp);

public slots:
    void SendInfo(const QString & message);
    void SendWarning(const QString & message);
    void SendError(const QString & message);
};

#endif // NOTIFICATIONSYSTEM_H
