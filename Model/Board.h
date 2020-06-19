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
    /**
     * @brief board is a 2D vector that represents a machine readable
     * format to the GUI application.
     */
    vector<vector<BoardMarks>> board_;
    /**
     * @brief boardSize is the number of rows or columns in the board.
     * a 3x3 board has a boardSize of 3.
     */
    size_t boardSize_;

public:
    /**
     * @brief Constructs a board given a board size.
     * @param size is the number of rows or columns in the board.
     */
    Board(size_t size);
    /**
     * @brief Board copy constructor.
     * @param b: The board to be copied.
     */
    Board(Board& b);
    /**
     * @brief Board move constructor.
     * @param b: The board to be moved.
     */
    Board(Board&& b);
    /**
     * @brief This assignment operator implements the copy & swap idiom,
     * so it works as a move and a copy assignment operator.
     * @param b: The board to be copied or moved.
     * @return a reference to this object, so this operator can be chained.
     */
    Board& operator=(Board b);
    /**
     * @brief Board destructor
     */
    virtual ~Board();
    /**
     * @brief evaluateBoard evaluates whether the state of the current board.
     * the function can evaluate to X wins or O wins or a Tie or No Winner.
     * @return the state of the current board.
     */
    virtual BoardState evaluateBoard() const;
    /**
     * @brief setPlayerInput sets the board with the mark given in the specified location.
     * after boundary checking the input row and column, and if the game hasen't reached a final state.
     * @param row of the cell target.
     * @param col of the cell target.
     * @param currentPlayer is the mark of the current player.
     * @return whether the update was successfull or not based on the boundary check and
     * validity of input given the board state.
     * @throws out_of_range exception when the row or column is out of bounds.
     */
    virtual bool setPlayerInput(size_t row, size_t col, BoardMarks currentPlayer);
    /**
     * @brief at is a getter function that returns a cell given a row and a column.
     * @param row of the cell target.
     * @param col of the cell target.
     * @return the value mark at the cell.
     * @throws out_of_range exception when the row or column is out of bounds.
     */
    virtual BoardMarks at(size_t row, size_t col) const;
    /**
     * @brief reset allows resetting the whole board, marking all the cells as empty.
     */
    virtual void reset();
    /**
     * @brief resetCell allows resetting a given cell to an empty type,
     * without the extra state checks done in the setPlayerInput function.
     */
    virtual void resetCell(size_t row, size_t col);
    /**
     * @brief size is a getter functions of the board size.
     * @return the size of the board i.e. numebr of rows or columns.
     */
    size_t size() const;
#ifdef QT_DEBUG
    virtual void printBoard () const;
#endif
};

#endif // BOARD_H
