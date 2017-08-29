#include "cell.h"

Cell::Cell(int row, int column, int type, bool visible) :
    m_row(row),
    m_column(column),
    m_type(type),
    m_visible(visible)
{
}

int Cell::getType() const
{
    return m_type;
}

bool Cell::getVisible() const
{
    return m_visible;
}

void Cell::makeVisible()
{
    m_visible = true;
}

void Cell::makeUnvisible()
{
    m_visible = false;
}

int Cell::getColumn() const
{
    return m_column;
}

void Cell::setColumn(int column)
{
    m_column = column;
}

int Cell::getRow() const
{
    return m_row;
}

void Cell::setRow(int row)
{
    m_row = row;
}

