#include <QDebug>
#include "gamefieldmodel.h"

#include <QSet>

#include "../utils/utils.h"

#include <QTimer>
#include <QEventLoop>

GameFieldModel::GameFieldModel(QObject *parent) :
    QAbstractListModel(parent),
    m_utility(std::shared_ptr<GameUtility>(new GameUtility("/home/work/Desktop/settings.json")))
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


void GameFieldModel::swapRange(int from, int to, int range)
{
    for (int startRange = 0; startRange < range; startRange++) {
        verticalSwap(from + (startRange * getGameFieldColumn()), to + (startRange * getGameFieldColumn()));
    }
}

void GameFieldModel::swap(int fromPosition, int toPosition)
{
    int rowStartObject = Utils::findRow(fromPosition, getGameFieldRow());
    int columnStartObject = Utils::findColumn(fromPosition, getGameFieldColumn());

    int rowFinishObject = Utils::findRow(toPosition, getGameFieldRow());
    int columnFinishObject = Utils::findColumn(toPosition, getGameFieldColumn());

    if (rowStartObject == rowFinishObject) {
        if (toPosition > fromPosition) {
            beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition+1);
        } else {
            beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition);
        }

        m_utility->swapCells(fromPosition, toPosition);

        endMoveRows();
    }

    if (columnStartObject == columnFinishObject) {
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

            QEventLoop loop;
            QTimer::singleShot(400, &loop, SLOT(quit()));
            loop.exec();

            m_utility->getCellByIndex(deleteIndex)->resetType();
            emit dataChanged(index(deleteIndex, 0), index(deleteIndex, 0));

            continue;
        }
        verticalSwap(currentCellIndex, prevIndex);
        prevIndex = currentCellIndex;
    }
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
    //std::reverse(std::begin(deletedIndex), std::end(deletedIndex));

    for(int value : deletedIndex) {
        //deleteItem(value);
    }

    return deletedIndex.empty();
}

void GameFieldModel::fillEmptyCell()
{
    /*
    QEventLoop loop;
    QTimer::singleShot(200, &loop, SLOT(quit()));
    loop.exec();
*/
    //qDebug() << "change empty cell";



    //m_utility->replaceByRandomCell(5, true);
  //  emit dataChanged(index(0, 0), index(0, 0));

//    verticalSwap(0, 5);

    QEventLoop loop;

    int currentColumn = Utils::findColumn(25, getGameFieldColumn());

    qDebug() << currentColumn;


    for (int currentCellIndex = 25;
         currentCellIndex > currentColumn;
         currentCellIndex -= getGameFieldColumn()) {

        auto obj = m_utility->getCellByIndex(currentCellIndex);
        if (!obj->getType()) {
            qDebug() << currentCellIndex;

            QTimer::singleShot(500, &loop, SLOT(quit()));
            loop.exec();

            m_utility->replaceByRandomCell(currentColumn);
            emit dataChanged(index(currentColumn, 0), index(currentColumn, 0));

            //QEventLoop loop;
            QTimer::singleShot(500, &loop, SLOT(quit()));
            loop.exec();

            verticalSwap(currentColumn, currentCellIndex);
        }

    }


/*

    for (int currentCellIndex = 0;
         currentCellIndex < m_utility->getCollectionSize();
         currentCellIndex += getGameFieldColumn()) {

    }
    */
}
