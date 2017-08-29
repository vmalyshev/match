#ifndef SETTINGS_H
#define SETTINGS_H

#include <QList>

class Settings
{
public:
    Settings();

    int getRowCount() const;

    int getColumnCount() const;

    int getImageCount() const;

    int getSize() const;

private:
    int m_rowCount;
    int m_columnCount;
    int m_imageCount;

    QList<int> m_objectTypes;
};

#endif // SETTINGS_H
