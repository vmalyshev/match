#include "gameutility.h"

#include <QDebug>

#include "cell.h"
#include "../file/jsonmanager.h"

GameUtility::GameUtility(const QString &filename)
{
    m_settings = std::shared_ptr<Settings>((new JsonManager())->readFromFile(filename));
    m_cellFactory = std::shared_ptr<CellFactory>(new CellFactory(m_settings));
    generateField();
}

void GameUtility::generateField()
{
    m_cells.reserve(m_settings->getColumnCount() * m_settings->getRowCount());

    for (int row = 0; row < m_settings->getRowCount(); row++) {
        for (int column = 0; column < m_settings->getColumnCount(); column++) {

            if (!row) {
                m_cells.push_back(m_cellFactory->generateRandomCell(false));
            } else {
                m_cells.push_back(m_cellFactory->generateRandomCell(true));
            }
        }
    }
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

void GameUtility::replaceByRandomCell(int index, bool visible)
{
    m_cells.replace(index, m_cellFactory->generateRandomCell(visible));
}

int GameUtility::getCollectionSize()
{
    return m_cells.size();
}

