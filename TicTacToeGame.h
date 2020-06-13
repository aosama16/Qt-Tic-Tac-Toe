#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "board.h"

namespace Ui {
class TicTacToeGame;
}

class TicTacToeGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit TicTacToeGame(QWidget *parent = nullptr);
    ~TicTacToeGame();

private: // Data
    Ui::TicTacToeGame *ui;
    BoardMarks currentPlayer = BoardMarks::X;
    Board board;
};

#endif // MAINWINDOW_H
