#include "utils.h"

int Utils::findRow(int index, int rowCount)
{
    return index / rowCount;
}

int Utils::findColumn(int index, int columnCount)
{
    return index % columnCount;
}
