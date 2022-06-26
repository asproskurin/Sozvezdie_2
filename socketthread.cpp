#include "socketthread.h"

SocketThread::SocketThread(qintptr socketDescriptor, qint16 countRequest, QObject *parent)
    : QThread{parent}, socketDescriptor_(socketDescriptor),
      countRequest_(countRequest)
{

}

void SocketThread::run()
{
    std::chrono::nanoseconds requestTime = getCurrentTime();
    countRequest_++;
    emit requestDone(socketDescriptor_, countRequest_, requestTime);
}

std::chrono::nanoseconds SocketThread::getCurrentTime()
{
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
}
