#ifndef BOARD_H
#define BOARD_H
#include "TTTCommonTypes.h"
#include <QtGlobal>
#include <vector>

using std::vector;

class Board {

private: // Data
    vector<vector<BoardMarks>> board;
    int boardSize;

public:
    Board(int size);
    BoardState evaluateBoard();
    bool setPlayerInput(int row, int col, BoardMarks currentPlayer);
    BoardMarks at(int row, int col);
    void set(int row, int col, BoardMarks mark);
    void reset();
    int size();
#ifdef QT_DEBUG
    void printBoard();
#endif
};

#endif // BOARD_H
