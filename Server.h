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
    void slotRequestAnswer(qintptr socketDescriptor, qint16 countRequest,
                           std::chrono::nanoseconds requestTime);

private:
    std::chrono::nanoseconds getCurrentTime();
    QHash<qintptr, QTcpSocket*> sockets_;
    qint32 countRequest_;
    QTcpSocket* socket_;
    QThreadPool* threadPool_;
    std::chrono::nanoseconds lastRequest_;
    QByteArray data_;
    QByteArray correctRequest_;
};

#endif // SERVER_H
