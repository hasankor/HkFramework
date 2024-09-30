#ifndef ALISTMODELDATA_H
#define ALISTMODELDATA_H

#include <QVariant>
#include <QMap>

class AListModelData
{
public:
    //NOTE: derived class, pass value in constructor and insert map

    //    NOTE: derived class defines Roles like this
    //    enum AnimalRoles {
    //        TypeRole = Qt::UserRole + 1,
    //        SizeRole
    //    };

    QVariant data(const int &dataRole) const;
    bool update(const int &dataRole, const QVariant &data);

    virtual QHash<int, QByteArray> roles() const = 0;

protected:
    QMap<int, QVariant> mDatas;
};
#endif // ALISTMODELDATA_H
