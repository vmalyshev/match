#ifndef FILEOPERATION_H
#define FILEOPERATION_H

#include <memory>

#include <QString>

#include "./../gameField/settings.h"

class FileOperation {
public:
    virtual std::shared_ptr<Settings> readFromFile(const QString& filename) = 0;
};

#endif // FILEOPERATION_H
