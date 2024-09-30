#include "asyncudpdatasender.h"
#include <QDebug>
#include <QCoreApplication>
#include <QAbstractEventDispatcher>


//referanced by https://stackoverflow.com/questions/14993000/the-most-reliable-and-efficient-udp-packet-size 1472
static const uint BYTE_SIZE = 1024;

AsyncUDPDataSender::AsyncUDPDataSender(uint16_t pPort, const QHostAddress &pHost, const QHostAddress &pEthernetInterfaceAddress)
    : AThread()
    , mSocket(nullptr)
    , mHost(pHost)
    , mPort(pPort)
    , mEthernetInterfaceAddress(pEthernetInterfaceAddress)
{

}

AsyncUDPDataSender::~AsyncUDPDataSender()
{

}

void AsyncUDPDataSender::mainLoop()
{
    //TODO :  if you send multicast set mHost("224.0.0.2") or releated ip
    mSocket = new QUdpSocket;
    mSocket->open(QIODevice::WriteOnly);

    if(!mSocket->bind(mEthernetInterfaceAddress)){
        qDebug() << "BAsyncUDPDataSender::mainLoop bind error " << mSocket->error() << " mEthernetInterfaceAddress:" << mEthernetInterfaceAddress;
    }

    mSocket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
    while(!getShouldStop()) {
        QThread::currentThread()->eventDispatcher()->processEvents(QEventLoop::WaitForMoreEvents);
    }
    mSocket->close();
    mSocket->deleteLater();
}

void AsyncUDPDataSender::sendRawData(const char *data, uint size)
{
    uint index = 0;
    while(size != index) {
        uint sendSize = qMin(BYTE_SIZE, size-index);
        sendToRemote(data+index,  sendSize);
        index += sendSize;
    }
    qDebug() << "New Data ---------------------------------";
}

void AsyncUDPDataSender::send(const QByteArray &pBuffer)
{
    if(!makeMethodRunOnThisThread("send", Q_ARG(QByteArray, pBuffer))){
        return;
    }

    sendRawData(pBuffer.constData(), pBuffer.size());
}

bool AsyncUDPDataSender::sendToRemote(const char *data, uint len)
{
    if(mSocket->writeDatagram(data, len, mHost, mPort) == -1){
        qDebug() << this->objectName() << "BAsyncUDPDataSender::sendToRemote char* error while sending data " << mSocket->error();
        return false;
    }
    return true;
}
