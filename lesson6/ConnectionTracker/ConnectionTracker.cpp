#include "ConnectionTracker.h"
#include <QDebug>
#include <QMetaMethod>

ConnectionTracker::ConnectionTracker(QObject *parent)
    : QObject{parent}
{}

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


template<typename Sender, typename Signal, typename Receiver, typename Slot>
bool ConnectionTracker::TrackConnection(Sender *sender, Signal signal, Receiver *receiver, Slot slot, Qt::ConnectionType type)
{
    bool success = QObject::connect(sender, signal, receiver, slot, type);
    if(!success)
        return false;


    ConnectionInfo info;
    //TODO : ConnectionInfo CollectConnectionInfo(5 params)
    info.sender = sender;
    info.receiver = receiver;

    // Получаем информацию о сигнале и слоте через QMetaMethod
    int signalIndex = sender->metaObject()->indexOfSignal(QMetaMethod::fromSignal(signal).methodSignature().constData());
    int slotIndex = receiver->metaObject()->indexOfSlot  (QMetaMethod::fromSignal(slot  ).methodSignature().constData());
    if(signalIndex != -1)
    {
        info.signalSignature = sender->metaObject()->method(signalIndex).methodSignature(); //получаем сигнатуру по индексу метода
    }
    if(slotIndex != -1)
    {
        info.slotSignature = receiver->metaObject()->method(slotIndex).methodSignature();
    }
    info.type = type;
    //CollectConnectionInfo - end;

    //SaveParams
    int connectionId = m_nextConnectionId++;
    m_connections[connectionId] = info;
    m_objectConnetions[sender].insert(connectionId);
    m_objectConnetions[receiver].insert(connectionId);


    //emit Signal
    QString description = QString("Connection #%1: %2 -> %3")
                       .arg(connectionId)
                       .arg(info.signalSignature)
                       .arg(info.slotSignature);
    qDebug()<<"Tracked:" <<description;

    emit ConnectionAdded(description);
    return success;
}

void ConnectionTracker::ConnectionInfo::Dump() const
{
    auto senderInfo = QString("sender %1").arg(sender->metaObject()->className());
    auto receiverInfo = QString("receiver %1").arg(receiver->metaObject()->className());
    qDebug()<<sender<<senderInfo<<signalSignature
             <<receiver<<receiverInfo<<slotSignature;
}
