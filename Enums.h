#ifndef ENUMS_H
#define ENUMS_H
#include <QObject>
class Enums : public QObject
{
    Q_OBJECT
public:

    enum class ConnectionStatus : unsigned int{
        CONNECTED = 0,
        DIS_CONNECTED = 1
    };

    Q_ENUM(ConnectionStatus)
};

#endif // ENUMS_H
