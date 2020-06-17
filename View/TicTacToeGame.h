#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TTTCommonTypes.h"
#include <QDialog>
#include <vector>

using std::vector;

namespace Ui {
class TicTacToeGame;
}

class TicTacToeGame final : public QDialog
{
    Q_OBJECT

public:
    explicit TicTacToeGame(QWidget *parent = nullptr);
    ~TicTacToeGame();
    void updateCell(Cell &cell, BoardMarks currentPlayer);
    void declareGameState(BoardState boardState);
    vector<Cell> buildCellButtons(int boardSize);
    void reset(vector<Cell> &cells);

private:
    Ui::TicTacToeGame *ui;
    void setConnections();
    QString getPlayerText(BoardMarks currentPlayer);
    QString getPlayerStyleSheet(BoardMarks currentPlayer);
    QString getBoardFinalStateText(BoardState boardState);

signals:
    void newGame();
};

#endif // MAINWINDOW_H
