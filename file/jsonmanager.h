#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include "fileoperation.h"

class JsonManager : public FileOperation
{
public:
    JsonManager();

    std::shared_ptr<Settings> readFromFile(const QString &filename);
};

#endif // JSONMANAGER_H
