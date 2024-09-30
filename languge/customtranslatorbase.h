#ifndef CUSTOMTRANSLATORBASE_H
#define CUSTOMTRANSLATORBASE_H

#include <QMap>
#include <qtranslator.h>
class CustomTranslatorBase : public QTranslator
{
    Q_OBJECT
public:
    CustomTranslatorBase(QObject *parent = nullptr);

signals:
    void languageChanged();

public:
    void setCurrentLanguage(int pLanguageId);

    // QTranslator interface
public:
    QString translate(const char *context, const char *sourceText, const char *disambiguation = nullptr, int n = -1) const override;

    //derived class must be inherite
protected:
    virtual void fillLanguages() = 0;

protected:
    bool registerLanguage(const int &pLanguageId, const QMap<QString, QString> pLanguage);

private:
    int mCurrentLanguage;
    QMap<int, QMap<QString, QString>> mLanguageContainer;
};

#endif // CUSTOMTRANSLATORBASE_H
