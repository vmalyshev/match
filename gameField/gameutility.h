#ifndef GAMEUTILITY_H
#define GAMEUTILITY_H

#include <QList>
#include <QString>

#include <memory>

#include "cell.h"
#include "settings.h"
#include "factory/cellfactory.h"

class GameUtility
{
public:
    GameUtility(const QString& filename);

    void generateField();

    std::shared_ptr<Cell> getCellByIndex(int cellIndex);

    void swapCells(int fromPosition, int toPosition);

    std::shared_ptr<Settings> getSettings() const;

    void replaceByRandomCell(int index);

    int getCollectionSize();
private:
    QList<std::shared_ptr<Cell>> m_cells;

    std::shared_ptr<Settings> m_settings;

    std::shared_ptr<CellFactory> m_cellFactory;
};

#endif // GAMEUTILITY_H
