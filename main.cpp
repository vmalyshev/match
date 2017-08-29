#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtQml>

#include "gamefieldmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<GameFieldModel> ("game.ua", 1, 0, "GameModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
