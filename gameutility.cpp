#include "gameutility.h"

#include "cell.h"

#include <time.h>
#include <stdlib.h>

#include <QDebug>

GameUtility::GameUtility()
{
    srand (time(NULL));

    m_settings = std::shared_ptr<Settings>(new Settings());

    generateField();
}

void GameUtility::generateField()
{
    m_cells.reserve(m_settings->getColumnCount() * m_settings->getRowCount());

    for (int row = 0; row < m_settings->getRowCount(); row++) {
        for (int column = 0; column < m_settings->getColumnCount(); column++) {

            if (!row) {
                m_cells.push_back(generateRandomCell(row, column, false));
            } else {
                m_cells.push_back(generateRandomCell(row, column, true));
            }
        }
    }
}

bool GameUtility::checkGameField()
{

}


std::shared_ptr<Cell> GameUtility::getCellByIndex(int cellIndex)
{
    return m_cells.at(cellIndex);
}

void GameUtility::swapCells(int fromPosition, int toPosition)
{
    m_cells.swap(fromPosition, toPosition);
}

std::shared_ptr<Settings> GameUtility::getSettings() const
{
    return m_settings;
}

void GameUtility::addNewRandomCell(int index, bool visible)
{
    auto cell = getCellByIndex(index);
    m_cells.replace(index, generateRandomCell(cell->getRow(), cell->getColumn(), visible));
}

std::shared_ptr<Cell> GameUtility::generateRandomCell(int row, int column, bool visible)
{
    int rndType = rand() % m_settings->getImageCount() + 1;
    return std::shared_ptr<Cell>(new Cell(row, column, rndType, visible));
}

int GameUtility::findRow(int index)
{
    return index / m_settings->getColumnCount();
}

int GameUtility::findColumn(int index)
{
    return index % m_settings->getColumnCount();
}

