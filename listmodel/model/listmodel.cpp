#include "listmodel.h"
#include <QCryptographicHash>
#include <algorithm>
#include <QDataStream>
#include <QDebug>

ListModel::ListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    qRegisterMetaType<AListModelData*>("AListModelData*");
}

ListModel::~ListModel()
{
    clear();
}

void ListModel::addModelData(const qint64 &key, AListModelData *modelData)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    mModelDatas.append({key, modelData});
    endInsertRows();
    emit modelDataAdded(key, modelData);
}

int ListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return (int)mModelDatas.size();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mModelDatas.size())
        return QVariant();

    QPair<qint64, AListModelData*> tPair = mModelDatas.at(index.row());
    return tPair.second->data(role);
}

void ListModel::clear()
{
    beginResetModel();
    mModelDatas.erase(mModelDatas.begin(), mModelDatas.end());
    mModelDatas.clear();
    endResetModel();
    emit modelDatasCleared();
}

bool ListModel::updateData(const qint64 &key, const int &dataType, const QVariant data)
{
    int indexOfKey = getIndexFromKey(key);
    if(indexOfKey == -1){
        qDebug() << "ListModel::updateData out of index";
        return false;
    }

    if(mModelDatas[indexOfKey].second->data(dataType) == data){
        return false;
    }

    mModelDatas[indexOfKey].second->update(dataType, data);
    emit dataChanged(index(indexOfKey), index(indexOfKey));
    emit modelDataUpdated(key, dataType, data);
    return true;
}

QVariant ListModel::getModelData(const int pIndex, const int pDataType)
{
    if((pIndex < 0 ) || (pIndex >= (int)mModelDatas.size())) {
        qDebug() << "ListModel::getModelData out of index";
        return QVariant();
    }
    return mModelDatas.at(pIndex).second->data(pDataType);
}

bool ListModel::remove(const qint64 &key)
{
    int indexOfKey = getIndexFromKey(key);
    if(indexOfKey == -1){
        qDebug() << "ListModel::remove out of index";
        return false;
    }
    beginRemoveRows(QModelIndex(), indexOfKey, indexOfKey);
    mModelDatas.removeAt(indexOfKey);
    endRemoveRows();
    emit modelDataRemoved(key);
    return true;
}

bool ListModel::isContain(const qint64 &key)
{
    if(getData(key) == nullptr){
        return false;
    }
    return true;
}

int ListModel::size()
{
    return (int)mModelDatas.size();
}

AListModelData *ListModel::getData(const qint64 &key)
{
    for (auto &tIter : mModelDatas) {
        if(tIter.first == key){
            return tIter.second;
        }
    }
    return nullptr;
}

QPair<qint64, AListModelData *> ListModel::getRow(const int &rowIndex)
{
    if(rowIndex >= mModelDatas.size()){
        return qMakePair(-1, nullptr);
    }
    return mModelDatas.at(rowIndex);
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    if(mModelDatas.size() == 0){
        return QHash<int, QByteArray>();
    }
    return mModelDatas.at(0).second->roles();
}

qint64 ListModel::hash(const QString &str)
{
    QByteArray hash = QCryptographicHash::hash(
                QByteArray::fromRawData((const char*)str.utf16(), str.length()*2),
                QCryptographicHash::Md5
                );
    Q_ASSERT(hash.size() == 16);
    QDataStream stream(hash);
    qint64 a, b;
    stream >> a >> b;
    return a ^ b;
}

int ListModel::getIndexFromKey(const qint64 &key)
{
    for (int i = 0; i < mModelDatas.size(); ++i) {
        if(mModelDatas.at(i).first == key){
            return i;
        }
    }
    return -1;
}
