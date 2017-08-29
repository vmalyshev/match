#ifndef GAMEUTILITY_H
#define GAMEUTILITY_H

#include <memory>

#include "cell.h"
#include "settings.h"

#include <QList>

class GameUtility
{
public:
    GameUtility();

    void generateField();

    bool checkGameField();

    std::shared_ptr<Cell> getCellByIndex(int cellIndex);

    void swapCells(int fromPosition, int toPosition);

    std::shared_ptr<Settings> getSettings() const;

    void addNewRandomCell(int index, bool visible = true);

    int findRow(int index);
    int findColumn(int index);
private:
    QList<std::shared_ptr<Cell>> m_cells;

    std::shared_ptr<Cell> generateRandomCell(int row, int column, bool visible = true);

    std::shared_ptr<Settings> m_settings;

};

#endif // GAMEUTILITY_H
