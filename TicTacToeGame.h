#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class TicTacToeGame;
}

class TicTacToeGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit TicTacToeGame(QWidget *parent = nullptr);
    ~TicTacToeGame();

private:
    Ui::TicTacToeGame *ui;
};

#endif // MAINWINDOW_H
