#include "settings.h"

Settings::Settings()
{
    m_rowCount = 5;
    m_columnCount = 5;
    m_imageCount = 3;
}

int Settings::getRowCount() const
{
    return m_rowCount + 1;
}

int Settings::getColumnCount() const
{
    return m_columnCount;
}

int Settings::getImageCount() const
{
    return m_imageCount;
}

int Settings::getSize() const
{
    return m_columnCount * (m_rowCount + 1);
}
