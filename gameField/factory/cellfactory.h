#ifndef CELLFACTORY_H
#define CELLFACTORY_H

#include <memory>

#include "../cell.h"
#include "../settings.h"

//Little fake factory
class CellFactory
{
public:
    CellFactory(std::shared_ptr<Settings>& settings);

    std::shared_ptr<Cell> generateRandomCell(bool visible);

    std::shared_ptr<Cell> generateCell(int type, bool visible);
private:
    std::shared_ptr<Settings> m_settings;
};

#endif // CELLFACTORY_H
