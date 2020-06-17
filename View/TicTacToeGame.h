#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TTTCommonTypes.h"
#include <QDialog>
#include <vector>

using std::vector;

namespace Ui {
class TicTacToeGame;
}

/**
 * @brief The TicTacToeGame class is responsible for the GUI of a game,
 * it is responsible for building the cells of a board, which can be of
 * variable size, and a navigation button to take the user back to
 * the title screen, and a button for resetting the game and playing a
 * new one.
 */

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
