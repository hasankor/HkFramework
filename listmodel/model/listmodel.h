#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractListModel>
#include <listmodel/adata/alistmodeldata.h>

class ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ListModel(QObject *parent = 0);
    ~ListModel();

    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

signals:
    void modelDatasCleared();
    void modelDataRemoved(const qint64 &key);
    void modelDataAdded(const qint64 &key, AListModelData *modelData);
    void modelDataUpdated(const qint64 &key, const int &dataType, const QVariant data);

public:
    Q_INVOKABLE bool updateData(const qint64 &key, const int &dataType, const QVariant data);

    Q_INVOKABLE QVariant getModelData(const int pIndex, const int pDataType);

    Q_INVOKABLE int size();

public:
    void clear();

    void addModelData(const qint64 &key, AListModelData *modelData);

    bool remove(const qint64 &key);

    bool isContain(const qint64 &key);

    AListModelData* getData(const qint64 &key);

    QPair<qint64, AListModelData*> getRow(const int &rowIndex);

    qint64 hash(const QString &str);

private:
    int getIndexFromKey(const qint64 &key);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<QPair<qint64, AListModelData*>> mModelDatas;
};

#endif // LISTMODEL_H
