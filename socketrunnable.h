#ifndef SOCKETRUNNABLE_H
#define SOCKETRUNNABLE_H

#include <QRunnable>
#include <QTcpSocket>
#include <QTime>
#include <chrono>

class SocketRunnable : public QRunnable
{
public:
    SocketRunnable(qintptr socketDescriptor, qint16 countRequest,
                   std::chrono::nanoseconds requestTime);
    void run();

private:
    QTcpSocket* socket_;
    qintptr socketDescriptor_;
    qint16 countRequest_;
    std::chrono::nanoseconds requestTime_;
};

#endif // SOCKETRUNNABLE_H
