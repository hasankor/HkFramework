#include "customtranslatorbase.h"
#include <QDebug>

CustomTranslatorBase::CustomTranslatorBase(QObject *parent)
    : QTranslator(parent)
    , mCurrentLanguage(0)
{

}

void CustomTranslatorBase::setCurrentLanguage(int pLanguageId)
{
    mCurrentLanguage = pLanguageId;
    emit languageChanged();
}

QString CustomTranslatorBase::translate(const char *context, const char *sourceText, const char *disambiguation, int n) const
{
    Q_UNUSED(context)
    Q_UNUSED(disambiguation)
    Q_UNUSED(n)

    QString tSourceText = QString(sourceText);

    auto tIterLanguge = mLanguageContainer.find(mCurrentLanguage);
    if(tIterLanguge == mLanguageContainer.end()){
        return tSourceText;
    }

    auto tIterTranslation = tIterLanguge.value().find(tSourceText);
    if(tIterTranslation == tIterLanguge.value().end()){
        return tSourceText;
    }

    return tIterTranslation.value();
}

bool CustomTranslatorBase::registerLanguage(const int &pLanguageId, const QMap<QString, QString> pLanguage)
{
    auto tIter = mLanguageContainer.find(pLanguageId);
    if(tIter != mLanguageContainer.end()){
        qDebug() << "CustomTranslatorBase::insertLanguageToContainer has been added, Id:" << pLanguageId;
        return false;
    }

    mLanguageContainer.insert(pLanguageId, pLanguage);
    return true;
}
