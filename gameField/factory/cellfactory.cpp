#include "cellfactory.h"

#include <time.h>
#include <stdlib.h>

CellFactory::CellFactory(std::shared_ptr<Settings>& settings):
    m_settings(settings)
{
    srand(time(NULL));
}

std::shared_ptr<Cell> CellFactory::generateRandomCell()
{
    int rndType = rand() % m_settings->getObjectCount() + 1;
    return generateCell(m_settings->getTypeByIndex(rndType));
}

std::shared_ptr<Cell> CellFactory::generateCell(int type)
{
    return std::shared_ptr<Cell>(new Cell(type));
}
