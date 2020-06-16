INCLUDEPATH += \
    .. \
    ../AI \
    ../Model \
    ../View \
    ../Controller \
    ../Forms

SOURCES += \
    ../AI/MiniMaxAgent.cpp \
    ../Model/Board.cpp \
    ../View/TicTacToeGame.cpp \
    ../View/TitleScreen.cpp \
    ../Controller/TTTController.cpp

HEADERS += \
    ../AI/AIAgent.h \
    ../AI/NoAgent.h \
    ../AI/MiniMaxAgent.h \
    ../Model/Board.h \
    ../View/TicTacToeGame.h \
    ../View/TitleScreen.h \
    ../Controller/TTTController.h \
    ../TTTCommonTypes.h

FORMS += \
    ../Forms/TicTacToeGame.ui \
    ../Forms/titlescreen.ui
