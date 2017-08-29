#ifndef GAMEFIELDMODEL_H
#define GAMEFIELDMODEL_H

#include <QObject>

#include <memory>
#include <QAbstractListModel>
#include <QAbstractTableModel>

#include "settings.h"
#include "gameutility.h"

class GameFieldModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int gameFieldRow READ getGameFieldRow CONSTANT)
    Q_PROPERTY(int gameFieldColumn READ getGameFieldColumn CONSTANT)

public:
    enum Roles {
        Type = Qt::UserRole + 1,
        Row,
        Column,
        Visible
    };

    explicit GameFieldModel(QObject *parent = nullptr);

    int getGameFieldRow() const;
    int getGameFieldColumn() const;

    int rowCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void swapItem(int fromIndex, int toIndex);

    void swap(int fromPosition, int toPosition);


    void swapScreens(int index1, int index2);

    void swapRange(int from, int to, int range);

    Q_INVOKABLE void checkMatch();
private:
    std::shared_ptr<GameUtility> m_utility;

    void deleteItem(int deleteIndex);

    inline void addMatch(QList<int>& deletedIndex, int firstIndex, int secondIndex, int thirdIndex);

signals:
    void swapRun(int index);
public slots:

};

#endif // GAMEFIELDMODEL_H
