#include "TicTacToeGame.h"
#include "titlescreen.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    qApp->setQuitOnLastWindowClosed(false);

    QApplication a(argc, argv);
    TitleScreen mainScreen;
    QObject::connect(&mainScreen, &TitleScreen::exited, &a, &QApplication::quit);
    mainScreen.show();

    return a.exec();
}
