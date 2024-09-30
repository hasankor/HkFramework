#include "asyncudpdatareceiver.h"
#include <QCoreApplication>
#include <QAbstractEventDispatcher>
#include <QDebug>

AsyncUDPDataReceiver::AsyncUDPDataReceiver(const uint16_t &pPort, const QHostAddress &pHost, const QHostAddress &pEthernetInterfaceAddress)
    : AThread()
    , mHost(pHost)
    , mPort(pPort)
    , mEthernetInterfaceAddress(pEthernetInterfaceAddress)
    , mSocket(nullptr)
{

}

AsyncUDPDataReceiver::~AsyncUDPDataReceiver()
{
    if(mHost.isMulticast()){
        closeMulticast();
    }else {
        closeUnicast();
    }
}

void AsyncUDPDataReceiver::mainLoop()
{
    mSocket = new QUdpSocket;
    mSocket->open(QIODevice::ReadOnly);

    if(mHost.isMulticast()){
        bindMulticast();
    }else {
        bindUnicast();
    }
    mSocket->setSocketOption(QAbstractSocket::MulticastTtlOption, 2);

    QObject::connect(mSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
    QObject::connect(mSocket, &QUdpSocket::readyRead, this, &AsyncUDPDataReceiver::readAvaliableData, Qt::QueuedConnection);

    while(!getShouldStop()) {
        if(mSocket->waitForReadyRead(TIME_OUT)) {
            readAvaliableData();
        }
    }

    QObject::disconnect(mSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));

    if(mHost.isMulticast()){
        closeMulticast();
    }else {
        closeUnicast();
    }
}

void AsyncUDPDataReceiver::error(QAbstractSocket::SocketError error)
{
    if((error != QAbstractSocket::SocketTimeoutError) && (error != QAbstractSocket::TemporaryError)){
        qDebug() << this->objectName() << "BAsyncUDPDataReceiver::error error " << error;
    }
}

void AsyncUDPDataReceiver::readAvaliableData()
{
    QByteArray tBuffer;
    tBuffer.resize(mSocket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;
    mSocket->readDatagram(tBuffer.data(), tBuffer.size(), &sender, &senderPort);
    emit newMessageFromRemote(tBuffer);
}

bool AsyncUDPDataReceiver::bindMulticast()
{
    if(!mSocket->bind(mEthernetInterfaceAddress, mPort, QUdpSocket::ShareAddress)){
        qDebug() << this->objectName() << "BAsyncUDPDataReceiver::bindMulticast QUDPSocket bind error " << mSocket->error()  << " mPort:" << mPort << " mHost:" << mHost;
        return false;
    }

    if(!mSocket->joinMulticastGroup(mHost)){
        qDebug() << this->objectName() << "BAsyncUDPDataReceiver::bindMulticast QUDPSocket joinMulticastGroup error " << mSocket->error() << " mPort:" << mPort << " mHost:" << mHost;
        return false;
    }
    qDebug() << this->objectName() << "BAsyncUDPDataReceiver::bindMulticast successfully";
    return true;
}

bool AsyncUDPDataReceiver::bindUnicast()
{
    if(!mSocket->bind(mEthernetInterfaceAddress, mPort)){
        qDebug() << this->objectName() << "BAsyncUDPDataReceiver::bindUnicast QUDPSocket bind error " << mSocket->error() << " mPort:" << mPort << " mHost:" << mHost;
        return false;
    }
    qDebug() << this->objectName() << "BAsyncUDPDataReceiver::bindUnicast successfully";
    return true;
}

void AsyncUDPDataReceiver::closeMulticast()
{
    if(mSocket){
        mSocket->leaveMulticastGroup(mHost);
       deleteSocket();
    }
}

void AsyncUDPDataReceiver::closeUnicast()
{
   deleteSocket();
}

void AsyncUDPDataReceiver::deleteSocket()
{
    if(mSocket){
        mSocket->close();
        mSocket->deleteLater();
        mSocket = nullptr;
    }
}
