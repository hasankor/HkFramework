#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <qtcpsocket.h>
#include <thread/athread.h>
#include <healtchecker/healthchecker.h>

class TcpClient : public AThread
{
    Q_OBJECT
    Q_PROPERTY(HealthChecker* healthStatus READ healthStatus CONSTANT)
public:
    explicit TcpClient(QString pIp = "192.168.10.200", short pPort = 8888);

    HealthChecker* healthStatus() const;

signals:
    void newMessage(QByteArray pBuffer);

public slots:
    void writeMessage(QByteArray pBuffer);

    // AThread interface
protected:
    void mainLoop();

private slots:
    void reConnectToHost();

private:
    HealthChecker* mHealthStatus;
    QTcpSocket *mSocket;
    QString mIp;
    short mPort;
};

#endif // TCPCLIENT_H
