#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QTime>
#include <chrono>

class SocketThread : public QThread
{
    Q_OBJECT

public:
    explicit SocketThread(qintptr socketDescriptor,
                          qint16 countRequest, QObject *parent = nullptr);
    void run();

signals:
    void requestDone(qintptr socketDescriptor,
                     qint16 countRequest, std::chrono::nanoseconds requestTime);

private:
    std::chrono::nanoseconds getCurrentTime();
    qintptr socketDescriptor_;
    qint16 countRequest_;
};

#endif // SOCKETTHREAD_H
