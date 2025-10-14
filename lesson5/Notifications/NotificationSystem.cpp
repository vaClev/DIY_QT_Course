#include "NotificationSystem.h"
#include <QString>
#include <QDateTime>
#include <QDebug>

//Private constructor
NotificationSystem::NotificationSystem(QObject *parent)
    : QObject{parent}
{
}

//static singletone instance
NotificationSystem &NotificationSystem::Instance()
{
    static NotificationSystem instance;
    return instance;
}


//----------
//slots definitions - start
void NotificationSystem::SendInfo(const QString & message)
{
    qDebug()<< "INFO" << message;
    emit InfoMessage(message);
    emit MessageReceived("INFO", message, QDateTime::currentDateTime());
}

void NotificationSystem::SendWarning(const QString & message)
{
    qDebug()<< "WARNING" << message;
    emit WarningMessage(message);
    emit MessageReceived("WARNING", message, QDateTime::currentDateTime());
}

void NotificationSystem::SendError(const QString & message)
{
    qDebug()<< "ERROR" << message;
    emit ErrorMessage(message);
    emit MessageReceived("ERROR", message, QDateTime::currentDateTime());
}
//----------
//slots definitions - end
