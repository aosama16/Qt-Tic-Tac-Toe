#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <vector>
#include "board.h"

namespace Ui {
class TicTacToeGame;
}

class TicTacToeGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit TicTacToeGame(QWidget *parent = nullptr, int boardSize = 3);
    ~TicTacToeGame();

private: // Types
    struct Cell{
        QPushButton *cellBtn = nullptr;
        int row = -1;
        int col = -1;
        Cell(QPushButton *cellBtn, int row, int col):
            cellBtn(cellBtn),
            row(row),
            col(col)
        {}

    };

private: // Data
    Ui::TicTacToeGame *ui;
    BoardMarks currentPlayer;
    Board board;
    std::vector<Cell> cells;
    bool AIopponent;
    bool startWithAI;

private: // Methods
    void setConnections();
    void switchPlayer();
    QString getCurrentPlayerText();
    QString getCurrentPlayerStyleSheet();
    QString getBoardFinalStateText(BoardState boardState);
    void declareGameState(BoardState boardState);
    void updateGameState(Cell& cell);

    void buildCellButtons(int boardSize);

signals:
    void turnFinished();

public slots:
    void cellClicked(Cell &cell);
    void playAIturn();
    void reset();
};

#endif // MAINWINDOW_H
