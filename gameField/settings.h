#ifndef SETTINGS_H
#define SETTINGS_H

#include <QList>

class Settings
{
public:
    Settings();

    void setRow(int row);
    int getRowCount() const;

    void setColumn(int column);
    int getColumnCount() const;

    int getElementScore() const;
    void setElementScore(int elementScore);

    int getMinScore() const;
    void setMinScore(int minScore);

    int getMaxMoves() const;
    void setMaxMoves(int maxMoves);

    void addType(int type);
    int getObjectCount() const;
    int getTypeByIndex(int index);

    int getSize() const;
private:
    int m_rowCount;
    int m_columnCount;
    int m_elementScore;
    int m_minScore;
    int m_maxMoves;


    QList<int> m_objectTypes;
};

#endif // SETTINGS_H
