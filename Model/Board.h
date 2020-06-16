#ifndef BOARD_H
#define BOARD_H
#include "TTTCommonTypes.h"
#include <QtGlobal>
#include <vector>

using std::vector;

class Board {

private: // Data
    vector<vector<BoardMarks>> board;
    const int boardSize;

public:
    Board(int size);
    virtual ~Board();
    virtual BoardState evaluateBoard() const;
    virtual bool setPlayerInput(int row, int col, BoardMarks currentPlayer);
    virtual BoardMarks at(int row, int col) const;
    virtual void reset();
    virtual bool resetCell(int row, int col);
    int size() const;
#ifdef QT_DEBUG
    virtual void printBoard () const;
#endif
};

#endif // BOARD_H
