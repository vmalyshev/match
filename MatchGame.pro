TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    model/gamefieldmodel.cpp \
    gameField/settings.cpp \
    gameField/gameutility.cpp \
    gameField/cell.cpp \
    file/jsonmanager.cpp \
    gameField/factory/cellfactory.cpp \
    utils/utils.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    model/gamefieldmodel.h \
    gameField/settings.h \
    gameField/gameutility.h \
    gameField/cell.h \
    file/fileoperation.h \
    file/jsonmanager.h \
    gameField/factory/cellfactory.h \
    utils/utils.h
