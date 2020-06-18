#-------------------------------------------------
#
# Project created by QtCreator 2020-06-13T19:45:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt-Tic-Tac-Toe
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

INCLUDEPATH += \
    AI \
    Model \
    View \
    Controller \
    Forms

SOURCES += \
    main.cpp \
    AI/MiniMaxAgent.cpp \
    Model/Board.cpp \
    View/TicTacToeGame.cpp \
    View/TitleScreen.cpp \
    Controller/TTTController.cpp

HEADERS += \
    AI/AIAgent.h \
    AI/NoAgent.h \
    AI/MiniMaxAgent.h \
    Model/Board.h \
    View/TicTacToeGame.h \
    View/TitleScreen.h \
    Controller/TTTController.h \
    TTTCommonTypes.h

FORMS += \
    Forms/TicTacToeGame.ui \
    Forms/titlescreen.ui

RC_ICONS = images/icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
