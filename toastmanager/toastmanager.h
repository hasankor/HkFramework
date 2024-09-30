#ifndef TOASTMANAGER_H
#define TOASTMANAGER_H

#include <QObject>

class ToastManager : public QObject
{
    Q_OBJECT
public:
    static ToastManager *getInstance();

signals:
    void showMessage(QString pText, QString pIconPath = QString(), int pDuration = DEFAULT_DURATION);
    void showSuccessMessage(QString pText, int pDuration = DEFAULT_DURATION);
    void showFailMessage(QString pText, int pDuration = DEFAULT_DURATION);

private:
    ToastManager(QObject *parent = nullptr);
    const static int DEFAULT_DURATION = 3000;

};

#endif // TOASTMANAGER_H
