#ifndef SETTINGSBASE_H
#define SETTINGSBASE_H

#include <QSettings>
class SettingsBase : public QSettings {

public:
    explicit SettingsBase(QObject *parent = nullptr);

protected:
    bool init();

protected:
    virtual void fillCommonSettings() = 0;

private:
    inline const static QString filename = "config.ini";
};


#endif // SETTINGSBASE_H
