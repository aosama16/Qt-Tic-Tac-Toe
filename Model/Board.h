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
    void reset();
    int size();
    virtual bool resetCell(int row, int col);
#ifdef QT_DEBUG
    void printBoard();
#endif
};

#endif // BOARD_H
