#include "ConnectionTracker.h"

ConnectionTracker::ConnectionTracker(QObject *parent)
    : QObject{parent}
{}

ConnectionTracker &ConnectionTracker::Instance()
{
    static ConnectionTracker instance;
    return instance;
}

void ConnectionTracker::DumpConnections() const
{
    for (auto && conn : m_connections)
    {
        conn.Dump();
    }
}

QList<QString> ConnectionTracker::GetConnectionsForObject(QObject *object) const
{
    //TODO : вернуть список коннекшнов для объекта
    return {};
}

bool ConnectionTracker::DisconnectAll(QObject *sender, QObject *receiver)
{
    //TODO : отключить указанные объекты
    return true;
}


void ConnectionTracker::ConnectionInfo::Dump() const
{
    qDebug()<<sender<<signalSignature<<receiver<<slotSignature;
}
