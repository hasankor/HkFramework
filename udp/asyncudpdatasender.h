#ifndef ASYNCUDPDATASENDER_H
#define ASYNCUDPDATASENDER_H

#include <QUdpSocket>
#include <thread/athread.h>

class AsyncUDPDataSender : public AThread
{
    Q_OBJECT
public:
    explicit AsyncUDPDataSender(uint16_t pPort, const QHostAddress &pHost, const QHostAddress &pEthernetInterfaceAddress = QHostAddress::AnyIPv4);
    virtual ~AsyncUDPDataSender();

public slots:
    void send(const QByteArray &pBuffer);

private:
    void sendRawData(const char *data, uint size);
    void mainLoop() override;
    bool sendToRemote(const char *data, uint len);

    QUdpSocket *mSocket;
    QHostAddress mHost;
    uint16_t mPort;
    QHostAddress mEthernetInterfaceAddress;
};

#endif // ASYNCUDPMESSAGESENDER_H
