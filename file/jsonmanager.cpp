#include "jsonmanager.h"

#include <QFileInfo>

JsonManager::JsonManager()
{
}

std::shared_ptr<Settings> JsonManager::readFromFile(const QString &filename)
{
    if (QFileInfo::exists(filename)) {
        return nullptr;
    }
}
