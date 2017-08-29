#include <QDebug>
#include "gamefieldmodel.h"

#include <QSet>

GameFieldModel::GameFieldModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_utility = std::shared_ptr<GameUtility>(new GameUtility());

    //checkMatch();

    //checkMatch();

}

int GameFieldModel::getGameFieldRow() const
{
    return m_utility->getSettings()->getRowCount();
}

int GameFieldModel::getGameFieldColumn() const
{
    return m_utility->getSettings()->getColumnCount();
}

int GameFieldModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return getGameFieldRow() * getGameFieldColumn();
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
    case Row:
        return currentCell->getRow();
    case Column:
        return currentCell->getColumn();
    case Visible:
        return currentCell->getVisible();
    }

    return QVariant();
}

QHash<int, QByteArray> GameFieldModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[Type] = "type";
    roles[Row] = "row";
    roles[Column] = "column";
    roles[Visible] = "visible";
    return roles;
}

void GameFieldModel::swapItem(int fromPosition, int toPosition)
{
    int rowStartObject = m_utility->findRow(fromPosition);
    int columnStartObject = m_utility->findColumn(fromPosition);

    int rowFinishObject = m_utility->findRow(toPosition);
    int columnFinishObject = m_utility->findColumn(toPosition);



    deleteItem(fromPosition);
}


void GameFieldModel::swapRange(int from, int to, int range)
{
    for (int startRange = 0; startRange < range; startRange++) {
        swapScreens(from + (startRange * getGameFieldColumn()), to + (startRange * getGameFieldColumn()));
    }
}

void GameFieldModel::swap(int fromPosition, int toPosition)
{
    int rowStartObject = m_utility->findRow(fromPosition);
    int columnStartObject = m_utility->findColumn(fromPosition);

    int rowFinishObject = m_utility->findRow(toPosition);
    int columnFinishObject = m_utility->findColumn(toPosition);


   // qDebug() << fromPosition << toPosition << (toPosition > fromPosition);
  //  if (columnStartObject == columnFinishObject) {
     //   if(toPosition > fromPosition) {

    /*
    beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition + 1);
    m_utility->swapCells(fromPosition, toPosition);
    endMoveRows();

    beginMoveRows(QModelIndex(), toPosition - 1, toPosition - 1, QModelIndex(), fromPosition);
    endMoveRows();
*/

    beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition + 1);
    m_utility->swapCells(fromPosition, toPosition);
    endMoveRows();

    beginMoveRows(QModelIndex(), toPosition - 1, toPosition - 1, QModelIndex(), fromPosition);
    endMoveRows();

/*
    if (rowStartObject == rowFinishObject) {
        if (toPosition > fromPosition) {
            beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition+1);
        } else {
            beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition);
        }
        m_utility->swapCells(fromPosition, toPosition);
        endMoveRows();
    }

*/
/*
    qDebug() << fromPosition << toPosition << (toPosition > fromPosition);
    if (columnStartObject == columnFinishObject) {
        if(toPosition > fromPosition) {

            beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition + 1);
            m_utility->swapCells(fromPosition, toPosition);
            endMoveRows();

            beginMoveRows(QModelIndex(), toPosition - 1, toPosition - 1, QModelIndex(), fromPosition);
            endMoveRows();
        } else {
            qDebug() << "-------";
            beginMoveRows(QModelIndex(), fromPosition, fromPosition, QModelIndex(), toPosition);
            m_utility->swapCells(fromPosition, toPosition);
            endMoveRows();

            beginMoveRows(QModelIndex(), toPosition + 1, toPosition + 1, QModelIndex(), fromPosition + 1);
            endMoveRows();
        }
    }
    */
}

void GameFieldModel::swapScreens(int index1, int index2)
{
    int min = index1 < index2 ? index1 : index2;
    int max = index1 > index2 ? index1 : index2;
    m_utility->swapCells(index1, index2);

    beginMoveRows(QModelIndex(), max, max, QModelIndex(), min);
    endMoveRows();

    if (max - min > 1) {
        beginMoveRows(QModelIndex(), min + 1, min + 1, QModelIndex(), max + 1);
        endMoveRows();
    }
}


void GameFieldModel::deleteItem(int deleteIndex)
{
    int currentColumn = m_utility->findColumn(deleteIndex);

   // int currentRow = m_utility->findRow(deleteIndex);

    int prevIndex = deleteIndex;


    for (int currentCellIndex = deleteIndex;
         currentCellIndex >= currentColumn;// + getGameFieldColumn();
         currentCellIndex -= getGameFieldColumn()) {

        if (deleteIndex == currentCellIndex) {

            beginRemoveRows(QModelIndex(), deleteIndex, deleteIndex);
            endRemoveRows();

            beginInsertRows(QModelIndex(), deleteIndex, deleteIndex);
            m_utility->addNewRandomCell(deleteIndex, false);
            endInsertRows();

            continue;
        }



swapScreens(currentCellIndex, prevIndex);
        //swapRange();
        //qDebug() << m_utility->getCellByIndex(prevIndex)->getVisible();

        //qDebug() << "position" << currentCellIndex << prevIndex;

        prevIndex = currentCellIndex;

       // emit dataChanged(index(prevIndex, 0), index(currentCellIndex, 0));
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

        deleteItem(firstIndex);
        deleteItem(secondIndex);
        deleteItem(thirdIndex);
    }
}

void GameFieldModel::checkMatch()
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
    std::reverse(std::begin(deletedIndex), std::end(deletedIndex));


    for(int value : deletedIndex) {
        //qDebug() << value;
        //deleteItem(value);
        //emit swapRun(value);
    }
}
