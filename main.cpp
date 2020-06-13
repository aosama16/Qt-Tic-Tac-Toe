#include "TicTacToeGame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TicTacToeGame w;
    w.show();

    return a.exec();
}
