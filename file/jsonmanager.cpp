#include "jsonmanager.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonValue>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>

JsonManager::JsonManager()
{
}

std::shared_ptr<Settings> JsonManager::readFromFile(const QString &filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        return nullptr;
    }

    auto settings = std::shared_ptr<Settings>(new Settings());

    QByteArray readData = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(readData);

    int row = document.object()["row"].toInt();
    settings->setRow(row);

    int column = document.object()["column"].toInt();
    settings->setColumn(column);

    QJsonArray types = document.object()["types"].toArray();
    for (auto type: types) {
        settings->addType(type.toInt());
    }

    int elementScore = document.object()["elementScore"].toInt();
    settings->setElementScore(elementScore);

    int minScore = document.object()["minScore"].toInt();
    settings->setMinScore(minScore);

    int maxMoves = document.object()["maxMoves"].toInt();
    settings->setMaxMoves(maxMoves);

    return settings;
}
