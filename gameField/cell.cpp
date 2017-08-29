#include "cell.h"

Cell::Cell(int type, bool visible) :
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
