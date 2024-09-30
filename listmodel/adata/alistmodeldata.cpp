#include "alistmodeldata.h"
#include <QDebug>

QVariant AListModelData::data(const int &dataRole) const
{
    if(!mDatas.contains(dataRole)){
        return QVariant();
    }
    return mDatas[dataRole];
}

bool AListModelData::update(const int &dataRole, const QVariant &data)
{
    if(!mDatas.contains(dataRole)){
        qDebug() << "AListModelData::update dataRole not found in mDatas, dataRole:" << dataRole;
        return false;
    }
    mDatas[dataRole] = data;
    return true;
}
