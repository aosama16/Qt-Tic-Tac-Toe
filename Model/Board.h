#ifndef BOARD_H
#define BOARD_H
#include "TTTCommonTypes.h"
#include <QtGlobal>
#include <vector>

using std::vector;

/**
 * @brief The Board class is responsible for representing
 * the underlying model of the game, it is a 2D matrix representation
 * of the GUI that is machine readable, and can be used when running
 * any sort of algorithms on the board.
 */

class Board
{

protected: // Data
    vector<vector<BoardMarks>> board_;
    const size_t boardSize_;

public:
    Board(size_t size);
    virtual ~Board();
    virtual BoardState evaluateBoard() const;
    virtual bool setPlayerInput(size_t row, size_t col, BoardMarks currentPlayer);
    virtual BoardMarks at(size_t row, size_t col) const;
    virtual void reset();
    virtual void resetCell(size_t row, size_t col);
    size_t size() const;
#ifdef QT_DEBUG
    virtual void printBoard () const;
#endif
};

#endif // BOARD_H
