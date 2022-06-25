#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QThreadPool>
#include <QHash>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server();
    ~Server();

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();

private:
    QHash<qintptr, QTcpSocket*> sockets;
    qint32 countRequest;
    QTcpSocket* socket;
    QThreadPool* threadPool;
};

#endif // SERVER_H
