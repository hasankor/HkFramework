#ifndef ASYNCUDPDATARECEIVER_H
#define ASYNCUDPDATARECEIVER_H

#include <QUdpSocket>

#include <thread/athread.h>

class AsyncUDPDataReceiver : public AThread
{
    Q_OBJECT
public:
    //unicast listen host must be 127.0.0.1 or local ip
    AsyncUDPDataReceiver(const uint16_t &pPort, const QHostAddress &pHost = QHostAddress::AnyIPv4, const QHostAddress &pEthernetInterfaceAddress = QHostAddress::AnyIPv4);
    ~AsyncUDPDataReceiver();


signals:
    void newMessageFromRemote(QByteArray pMessage);

protected:
    void mainLoop() override;

private slots:
    void error(QAbstractSocket::SocketError error);
    void readAvaliableData();

private:
    bool bindMulticast();
    bool bindUnicast();

    void closeMulticast();
    void closeUnicast();

    void deleteSocket();

private:
    QUdpSocket *mSocket;
    QHostAddress mHost;
    QHostAddress mEthernetInterfaceAddress;
    uint16_t mPort;

private:
    const static int TIME_OUT = 20;
};

#endif // ASYNCUDPDATARECEIVER_H
