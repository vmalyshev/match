#include <QDebug>
#include "gamefieldmodel.h"

#include <QSet>

#include "../utils/utils.h"

#include <QTimer>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>


#include <QThread>

#include <QWaitCondition>
#include <QMutex>



GameFieldModel::GameFieldModel(QObject *parent) :
    QAbstractListModel(parent),
    m_utility(std::shared_ptr<GameUtility>(new GameUtility(":/settings/file.json")))
{
}

int GameFieldModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_utility->getCollectionSize();
}

QVariant GameFieldModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    int currentItemIndex = static_cast<int>(index.row());

    auto currentCell = m_utility->getCellByIndex(currentItemIndex);

    switch (role) {
    case Type:
        return currentCell->getType();
    }

    return QVariant();
}

QHash<int, QByteArray> GameFieldModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[Type] = "type";
    return roles;
}

int GameFieldModel::getGameFieldRow() const
{
    return m_utility->getSettings()->getRowCount();
}

int GameFieldModel::getGameFieldColumn() const
{
    return m_utility->getSettings()->getColumnCount();
}

void GameFieldModel::swapItem(int fromPosition, int toPosition)
{
    //swap(fromPosition, toPosition);
    deleteItem(fromPosition);
}

void GameFieldModel::swap(int fromPosition, int toPosition)
{
    if (((fromPosition == toPosition + 1) || (fromPosition == toPosition - 1))) {
        if (toPosition > fromPosition) {
            beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition+1);
        } else {
            beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition);
        }
        m_utility->swapCells(fromPosition, toPosition);
        endMoveRows();
    }

    if (((fromPosition == toPosition + getGameFieldColumn()) || (fromPosition == toPosition - getGameFieldColumn()))) {
        verticalSwap(fromPosition, toPosition);
    }

}

void GameFieldModel::verticalSwap(int fromIndex, int toIndex)
{
    //int min = fromIndex < toIndex ? fromIndex : toIndex;
    //int max = fromIndex > toIndex ? fromIndex : toIndex;

    int min = std::min(fromIndex, toIndex);
    int max = std::max(fromIndex, toIndex);

    m_utility->swapCells(fromIndex, toIndex);

    beginMoveRows(QModelIndex(), max, max, QModelIndex(), min);
    endMoveRows();

    if (max - min > 1) {
        beginMoveRows(QModelIndex(), min + 1, min + 1, QModelIndex(), max + 1);
        endMoveRows();
    }
}

int GameFieldModel::getGameScore() const
{
    return m_gameScore;
}

void GameFieldModel::setGameScore(int gameScore)
{
    if (m_gameScore == gameScore)
        return;

    m_gameScore = gameScore;
    emit gameScoreChanged(gameScore);
}


void GameFieldModel::deleteItem(int deleteIndex)
{


    QEventLoop loop;
    int currentColumn = Utils::findColumn(deleteIndex, getGameFieldColumn());

    int prevIndex = deleteIndex;

    for (int currentCellIndex = deleteIndex;
         currentCellIndex >= currentColumn;
         currentCellIndex -= getGameFieldColumn()) {

        if (deleteIndex == currentCellIndex) {
            beginRemoveRows(QModelIndex(), deleteIndex, deleteIndex);
            endRemoveRows();

            beginInsertRows(QModelIndex(), deleteIndex, deleteIndex);
            m_utility->replaceByRandomCell(deleteIndex);
            endInsertRows();

            m_utility->getCellByIndex(deleteIndex)->resetType();
            emit dataChanged(index(deleteIndex, 0), index(deleteIndex, 0));

            continue;
        }
        verticalSwap(currentCellIndex, prevIndex);
        prevIndex = currentCellIndex;
    }

    fillEmptyCell(currentColumn + getGameFieldColumn());

    //QEventLoop loop;
    QTimer::singleShot(100, &loop, SLOT(quit()));
    loop.exec();

    //QEventLoop loop;
}

void GameFieldModel::addMatch(QList<int>& collection, int firstIndex, int secondIndex, int thirdIndex)
{
    int firstObjectType = m_utility->getCellByIndex(firstIndex)->getType();
    int secondObjectType = m_utility->getCellByIndex(secondIndex)->getType();
    int thirdObjectType = m_utility->getCellByIndex(thirdIndex)->getType();

    if ((firstObjectType == secondObjectType) && (secondObjectType == thirdObjectType)) {
        if (!collection.count(firstIndex)) {
            collection.push_back(firstIndex);
        }

        if (!collection.count(secondIndex)) {
            collection.push_back(secondIndex);
        }

        if (!collection.count(thirdIndex)) {
            collection.push_back(thirdIndex);
        }
    }
}


bool GameFieldModel::checkMatch()
{
    QList<int> deletedIndex;

    int windowSize = 3;

    for (int column = 0; column < getGameFieldColumn(); column++) {
        for (int selectIndex = column + getGameFieldColumn();
             selectIndex < (getGameFieldRow() - (windowSize - 1)) * getGameFieldColumn();
             selectIndex += getGameFieldColumn()) {

            int firstIndex = selectIndex;
            int secondIndex = firstIndex + getGameFieldColumn();
            int thirdIndex = secondIndex + getGameFieldColumn();

            addMatch(deletedIndex, firstIndex, secondIndex, thirdIndex);
        }
    }

    for (int row = 1; row < getGameFieldRow(); row++) {
        for (int selectIndex = getGameFieldColumn() * row;
             selectIndex < getGameFieldColumn() * row + getGameFieldColumn() - (windowSize - 1);
             selectIndex++) {

            addMatch(deletedIndex, selectIndex, selectIndex + 1, selectIndex + 2);
        }
    }

    std::sort(std::begin(deletedIndex), std::end(deletedIndex));

    for (int currentColumn = 0; currentColumn < getGameFieldColumn(); currentColumn++) {
        for(int currentIndex : deletedIndex) {
            if (Utils::findColumn(currentIndex, getGameFieldColumn()) == currentColumn) {
                deleteItem(currentIndex);
            }
        }
    }


    return deletedIndex.empty();
}

void GameFieldModel::fillEmptyCell(int itemIndex)
{
    int currentColumn = Utils::findColumn(itemIndex, getGameFieldColumn());

    auto obj = m_utility->getCellByIndex(itemIndex);
    if (!obj->getType()) {
        m_utility->replaceByRandomCell(currentColumn);
        emit dataChanged(index(currentColumn, 0), index(currentColumn, 0));
        verticalSwap(currentColumn, itemIndex);
    }
}
