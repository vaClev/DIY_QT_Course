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

QList<QString> ConnectionTracker::GetConnectionsForObject(QObject * object) const
{
    if(!object || !m_objectConnetions.contains(object))
        return {};

    QList<QString> results;
    for (auto && index : m_objectConnetions[object]) {
        results.push_back(m_connections[index].ToString());
    }
    return results;
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

QString ConnectionTracker::ConnectionInfo::ToString() const
{
    return QString("%1 %2 %3 %4").arg("sender ").arg(signalSignature).arg(" receiver ").arg(slotSignature);
}
