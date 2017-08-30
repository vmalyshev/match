#include "cell.h"

Cell::Cell(int type) :
    m_type(type)
{
}

int Cell::getType() const
{
    return m_type;
}

int Cell::resetType()
{
    m_type = 0;
}
