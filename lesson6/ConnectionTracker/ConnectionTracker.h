#ifndef CONNECTIONTRACKER_H
#define CONNECTIONTRACKER_H

#include <QObject>
#include <QHash>
#include <QSet>
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

#endif // CONNECTIONTRACKER_H
