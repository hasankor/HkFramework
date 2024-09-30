#ifndef HEALTHCHECKER_H
#define HEALTHCHECKER_H

#include <Enums.h>
#include <QObject>
#include <QTimer>

class HealthChecker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Enums::ConnectionStatus connectionStatus READ connectionStatus WRITE setConnectionStatus NOTIFY connectionStatusChanged)
public:
    /*!
     * \brief BHealthChecker
     * \param parent
     * \param pCheckIntervalMS
     * \details if pCheckIntervalMS == -1 keep alive a component forever
     */
    explicit HealthChecker(QObject *parent = nullptr, const int &pCheckIntervalMS = 1000, const int &pTimeoutMS = 3000);

    Enums::ConnectionStatus connectionStatus() const;

signals:
    void connectionStatusChanged(Enums::ConnectionStatus pConnectionStatus);

public slots:
    /*!
     * \brief handleAliveMessage
     * keep still alive connection of component
     */
    void handleAliveMessage();
    /*!
     * \brief handleKillMessage
     *  killed connection of component
     */
    void handleKillMessage();

private slots:
    void checkComponentAlive();
    void setConnectionStatus(Enums::ConnectionStatus pConnectionStatus);

private:
    QTimer *mTimer;
    quint16 mTimeoutMs;
    quint64 mLastMessageTimeMS;
    Enums::ConnectionStatus mConnectionStatus;
};
#endif // HEALTHCHECKER_H
