#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
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
    BoardMarks currentPlayer;
    Board board;

private: // Methods
    void setConnections();
    void switchPlayer();
    QString getCurrentPlayerText();
    QString getCurrentPlayerColor();
    QString getBoardFinalStateText(BoardState boardState);
    void declareGameState(BoardState boardState);

public slots:
    void cellClicked(QPushButton *cell, int row, int col);
    void reset();
};

#endif // MAINWINDOW_H
