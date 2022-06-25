#ifndef SOCKETRUNNABLE_H
#define SOCKETRUNNABLE_H

#include <QRunnable>
#include <QTcpSocket>
#include <QTime>
#include <chrono>

class socketRunnable : public QRunnable
{
public:
    socketRunnable(QTcpSocket* socket, qint16 countRequest,
                   std::chrono::nanoseconds requestTime);
    void run();

private:
    QTcpSocket* socket_;
    qint16 countRequest_;
    std::chrono::nanoseconds requestTime_;
};

#endif // SOCKETRUNNABLE_H
