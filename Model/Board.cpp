#include "Board.h"
#include <QString>
#ifdef QT_DEBUG
#include <QDebug>
#endif

Board::Board(size_t size)
    : board_(size, vector<BoardMarks>(size, BoardMarks::Empty)),
      boardSize_(size) {}

Board::~Board()
{

}

#ifdef QT_DEBUG
void Board::printBoard() const
{
    QString board;
    for (size_t row = 0; row < boardSize_; ++row) {
        for (size_t col = 0; col < boardSize_; ++col) {
            board += QString::number(static_cast<int>(board_[row][col]));
        }
        board += '\n';
    }
    qDebug().noquote() << board;
}
#endif

bool Board::setPlayerInput(size_t row, size_t col, BoardMarks currentPlayer)
{
    // The game is over, so no input is allowed untill game resets.
    if (BoardState::NoWinner != evaluateBoard())
        return false;

    // Row input in not valid.
    if (row >= boardSize_)
        return false;

    // Column input is not valid.
    if (col >= boardSize_)
        return false;

    // Cell is not empty.
    if (BoardMarks::Empty != board_[row][col])
        return false;

    // Update cell with current player's mark.
    board_[row][col] = currentPlayer;

    return true;
}

bool Board::resetCell(size_t row, size_t col)
{
    // Row input in not valid.
    if (row >= boardSize_)
        return false;

    // Column input is not valid.
    if (col >= boardSize_)
        return false;

    // Reset Cell
    board_[row][col] = BoardMarks::Empty;

    return true;
}

BoardMarks Board::at(size_t row, size_t col) const
{
    return board_.at(row).at(col);
}

BoardState Board::evaluateBoard() const
{
    // Checks rows for a win for the current player.
    for (size_t row = 0; row < boardSize_; ++row) {
        bool equalRow = true;
        BoardMarks ref = board_[row][0];
        for (size_t col = 1; col < boardSize_; ++col) {
            if (board_[row][col] != ref)
                equalRow = false;
        }
        if (equalRow) {
            if (BoardMarks::X == ref)
                return BoardState::XWins;
            if (BoardMarks::O == ref)
                return BoardState::OWins;
        }
    }

    // Checks columns for a win for the current player.
    for (size_t col = 0; col < boardSize_; ++col) {
        bool equalCol = true;
        BoardMarks ref = board_[0][col];
        for (size_t row = 1; row < boardSize_; ++row) {
            if (board_[row][col] != ref)
                equalCol = false;
        }
        if (equalCol) {
            if (BoardMarks::X == ref)
                return BoardState::XWins;
            if (BoardMarks::O == ref)
                return BoardState::OWins;
        }
    }

    // Checks diagonals for a win for the current player.
    bool equalDiagonal = true;
    BoardMarks ref = board_[0][0];
    for (size_t idx = 1; idx < boardSize_; ++idx) {
        if (board_[idx][idx] != ref)
            equalDiagonal = false;
    }
    if (equalDiagonal) {
        if (BoardMarks::X == ref)
            return BoardState::XWins;
        if (BoardMarks::O == ref)
            return BoardState::OWins;
    }

    equalDiagonal = true;
    ref = board_[0][boardSize_ - 1];
    for (size_t idx = 1; idx < boardSize_; ++idx) {
        int row = idx;
        int col = boardSize_ - idx - 1;
        if (board_[row][col] != ref)
            equalDiagonal = false;
    }
    if (equalDiagonal) {
        if (BoardMarks::X == ref)
            return BoardState::XWins;
        if (BoardMarks::O == ref)
            return BoardState::OWins;
    }

    // If there is an empty cell and no winner is determined, then the game is
    // still ongoing.
    for (size_t row = 0; row < boardSize_; ++row)
        for (size_t col = 0; col < boardSize_; ++col)
            if (BoardMarks::Empty == board_[row][col])
                return BoardState::NoWinner;

    // If no winner is determined and there are no empty cells, then the game is a
    // tie.
    return BoardState::Tie;
}

void Board::reset()
{
    // Sets all the cells to empty.
    for (size_t row = 0; row < boardSize_; ++row) {
        for (size_t col = 0; col < boardSize_; ++col) {
            board_[row][col] = BoardMarks::Empty;
        }
    }
}

size_t Board::size() const
{
    return boardSize_;
}
