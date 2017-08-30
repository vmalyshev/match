#include "settings.h"

Settings::Settings()
{
}

void Settings::setRow(int row)
{
    m_rowCount = row;
}

int Settings::getRowCount() const
{
    return m_rowCount + 1;
}

void Settings::setColumn(int column)
{
    m_columnCount = column;
}

int Settings::getColumnCount() const
{
    return m_columnCount;
}

int Settings::getObjectCount() const
{
    return m_objectTypes.size() - 1;
}

int Settings::getTypeByIndex(int index)
{
    return m_objectTypes.at(index);
}

int Settings::getSize() const
{
    return getRowCount() * getColumnCount();
}

int Settings::getElementScore() const
{
    return m_elementScore;
}

void Settings::setElementScore(int elementScore)
{
    m_elementScore = elementScore;
}

int Settings::getMinScore() const
{
    return m_minScore;
}

void Settings::setMinScore(int minScore)
{
    m_minScore = minScore;
}

int Settings::getMaxMoves() const
{
    return m_maxMoves;
}

void Settings::setMaxMoves(int maxMoves)
{
    m_maxMoves = maxMoves;
}

void Settings::addType(int type)
{
    m_objectTypes.push_back(type);
}
