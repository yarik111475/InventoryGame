QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = images/apple.ico
VERSION=1.0.0.0
DEFINES += APP_VERSION=\\\"$${VERSION}\\\"
QMAKE_TARGET_COMPANY = Iaroslav
QMAKE_TARGET_PRODUCT = Inventory Game
QMAKE_TARGET_DESCRIPTION = Simple game
QMAKE_TARGET_COPYRIGHT = Copyright (c) 2021 Iaroslav

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    InventoryItem.cpp \
    InventoryLabel.cpp \
    InventoryModel.cpp \
    InventoryView.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    InventoryItem.h \
    InventoryLabel.h \
    InventoryModel.h \
    InventoryView.h \
    MainWindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
