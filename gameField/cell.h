#ifndef CELL_H
#define CELL_H

class Cell
{
public:
    Cell(int type);

    int getType() const;

    int resetType();

private:
    int m_type;

    int m_row;
    int m_column;
};

#endif // CELL_H
