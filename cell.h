#ifndef CELL_H
#define CELL_H


class Cell
{
public:
    Cell(int row, int column, int type, bool visible);

    int getType() const;
    bool getVisible() const;
    void makeVisible();
    void makeUnvisible();

    int getColumn() const;
    void setColumn(int column);

    int getRow() const;
    void setRow(int row);

private:
    int m_type;
    bool m_visible;

    int m_row;
    int m_column;
};

#endif // CELL_H
