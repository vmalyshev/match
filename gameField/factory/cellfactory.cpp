#include "cellfactory.h"

#include <time.h>
#include <stdlib.h>

CellFactory::CellFactory(std::shared_ptr<Settings>& settings):
    m_settings(settings)
{
    srand(time(NULL));
}

std::shared_ptr<Cell> CellFactory::generateRandomCell(bool visible)
{
    int rndType = rand() % m_settings->getImageCount() + 1;
    return generateCell(rndType, visible);
}

std::shared_ptr<Cell> CellFactory::generateCell(int type, bool visible)
{
    return std::shared_ptr<Cell>(new Cell(type, visible));
}
