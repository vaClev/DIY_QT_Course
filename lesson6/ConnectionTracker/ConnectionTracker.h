#ifndef CONNECTIONTRACKER_H
#define CONNECTIONTRACKER_H

#include <QObject>
#include <QHash>
#include <QSet>
#include <QDebug>
#include <QMetaMethod>
////////////////////////////////////
//Класс для отслеживания соединений
////////////////////////////////////
class ConnectionTracker : public QObject
{
    Q_OBJECT

private:
    explicit ConnectionTracker(QObject *parent = nullptr);

public:
    static ConnectionTracker & Instance();

    template<typename Sender, typename Signal, typename Receiver, typename Slot>
    bool TrackConnection(Sender * sender, Signal signal, Receiver * receiver, Slot slot,
                         Qt::ConnectionType type = Qt::AutoConnection);

    void DumpConnections() const;

    //TODO: реализовать
    QList<QString> GetConnectionsForObject(QObject * object) const;
    //TODO: реализовать
    bool DisconnectAll(QObject * sender = nullptr, QObject * receiver = nullptr);


signals:
    void ConnectionAdded(const QString & description);
    void ConnectionRemoved(const QString & description);

private:
    struct ConnectionInfo
    {
        QObject * sender;
        QObject * receiver;
        QString signalSignature;
        QString slotSignature;
        Qt::ConnectionType type;
        void Dump() const;
    };

private:
    QHash<QObject*, QSet<int>> m_objectConnetions;
    QHash<int, ConnectionInfo> m_connections;
    int m_nextConnectionId{0};
};


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
    int slotIndex = receiver->metaObject()->indexOfSlot(QMetaMethod::fromSignal(slot).methodSignature().constData());
    if (slotIndex == -1) {
        // Если не нашли как слот, может быть это обычный метод?
        slotIndex = receiver->metaObject()->indexOfMethod(QMetaMethod::fromSignal(slot).methodSignature().constData());
    }
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



#endif // CONNECTIONTRACKER_H
