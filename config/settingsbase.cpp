#include "settingsbase.h"
#include <QFileInfo>
#include <QDebug>
#include <QTextCodec>
#include <QDir>

SettingsBase::SettingsBase(QObject *parent)
    : QSettings(filename, QSettings::IniFormat, parent){
    this->setIniCodec(QTextCodec::codecForName("UTF-8"));
}

bool SettingsBase::init()
{
    QFileInfo tFile(filename);
    bool flag = tFile.exists();
    if(!flag)
    {
        fillCommonSettings();
        sync();
        qDebug() << "Settings adding default values";
    }
    return flag;
}
