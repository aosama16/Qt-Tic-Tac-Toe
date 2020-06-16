#include "TicTacToeGame.h"
#include "TitleScreen.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    // Disabled QuitOnLastWindowClosed to avoid the dialog closing after QMessageBox is closed.
    qApp->setQuitOnLastWindowClosed(false);

    QApplication a(argc, argv);
    TitleScreen mainScreen;
    // The Main window must handle the close event manually to avoid the program running after closing it.
    QObject::connect(&mainScreen, &TitleScreen::exited, &a, &QApplication::quit);
    mainScreen.show();

    return a.exec();
}
