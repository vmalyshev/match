#ifndef GAMEFIELDMODEL_H
#define GAMEFIELDMODEL_H

#include <memory>

#include <QAbstractListModel>

#include "../gameField/settings.h"
#include "../gameField/gameutility.h"

class GameFieldModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int gameFieldRow READ getGameFieldRow CONSTANT)
    Q_PROPERTY(int gameFieldColumn READ getGameFieldColumn CONSTANT)
    Q_PROPERTY(int gameScore READ getGameScore WRITE setGameScore NOTIFY gameScoreChanged)
public:
    enum Roles {
        Type = Qt::UserRole + 1,
        Visible
    };

    explicit GameFieldModel(QObject *parent = nullptr);

    //override method from parent class
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    //swap items
    Q_INVOKABLE void swapItem(int fromIndex, int toIndex);
    void swap(int fromPosition, int toPosition);
    void verticalSwap(int fromIndex, int toIndex);
    void swapRange(int from, int to, int range);

    //sending score value to view
    int getGameScore() const;
    void setGameScore(int gameScore);

    //sending Row and Column value to view
    int getGameFieldRow() const;
    int getGameFieldColumn() const;

    //check and delete all matches on the game field
    Q_INVOKABLE void checkMatch();
private:
    int m_gameScore;
    std::shared_ptr<GameUtility> m_utility;

    void deleteItem(int deleteIndex);
    inline void addMatch(QList<int>& deletedIndex, int firstIndex, int secondIndex, int thirdIndex);
signals:
    void gameScoreChanged(int gameScore);

    void playerWon();
    void playerLost();
};

#endif // GAMEFIELDMODEL_H
