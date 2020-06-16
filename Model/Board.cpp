#include "Board.h"
#include <QString>
#ifdef QT_DEBUG
#include <QDebug>
#endif

Board::Board(int size)
    : board(size, vector<BoardMarks>(size, BoardMarks::Empty)),
      boardSize(size) {}

Board::~Board()
{

}

#ifdef QT_DEBUG
void Board::printBoard() const {
    QString board;
    for (int row = 0; row < this->boardSize; ++row) {
        for (int col = 0; col < this->boardSize; ++col) {
            board += QString::number(static_cast<int>(this->board[row][col]));
        }
        board += '\n';
    }
    qDebug().noquote() << board;
}
#endif

bool Board::setPlayerInput(int row, int col, BoardMarks currentPlayer) {
    // The game is over, so no input is allowed untill game resets.
    if (evaluateBoard() != BoardState::NoWinner)
        return false;

    // Row input in not valid.
    if (row >= this->boardSize || row < 0)
        return false;

    // Column input is not valid.
    if (col >= this->boardSize || col < 0)
        return false;

    // Cell is not empty.
    if (board[row][col] != BoardMarks::Empty)
        return false;

    // Update cell with current player's mark.
    this->board[row][col] = currentPlayer;

    return true;
}

bool Board::resetCell(int row, int col) {
    // Row input in not valid.
    if (row >= this->boardSize || row < 0)
        return false;

    // Column input is not valid.
    if (col >= this->boardSize || col < 0)
        return false;

    // Reset Cell
    this->board[row][col] = BoardMarks::Empty;

    return true;
}

BoardMarks Board::at(int row, int col) const { return board.at(row).at(col); }

BoardState Board::evaluateBoard() const {
    // Checks rows for a win for the current player.
    for (int row = 0; row < this->boardSize; ++row) {
        bool equalRow = true;
        BoardMarks ref = board[row][0];
        for (int col = 1; col < this->boardSize; ++col) {
            if (board[row][col] != ref)
                equalRow = false;
        }
        if (equalRow) {
            if (ref == BoardMarks::X)
                return BoardState::XWins;
            if (ref == BoardMarks::O)
                return BoardState::OWins;
        }
    }

    // Checks columns for a win for the current player.
    for (int col = 0; col < this->boardSize; ++col) {
        bool equalCol = true;
        BoardMarks ref = board[0][col];
        for (int row = 1; row < this->boardSize; ++row) {
            if (board[row][col] != ref)
                equalCol = false;
        }
        if (equalCol) {
            if (ref == BoardMarks::X)
                return BoardState::XWins;
            else if (ref == BoardMarks::O)
                return BoardState::OWins;
        }
    }

    // Checks diagonals for a win for the current player.
    bool equalDiagonal = true;
    BoardMarks ref = board[0][0];
    for (int idx = 1; idx < this->boardSize; ++idx) {
        if (board[idx][idx] != ref)
            equalDiagonal = false;
    }
    if (equalDiagonal) {
        if (ref == BoardMarks::X)
            return BoardState::XWins;
        else if (ref == BoardMarks::O)
            return BoardState::OWins;
    }

    equalDiagonal = true;
    ref = board[0][this->boardSize - 1];
    for (int idx = 1; idx < this->boardSize; ++idx) {
        int row = idx;
        int col = this->boardSize - idx - 1;
        if (board[row][col] != ref)
            equalDiagonal = false;
    }
    if (equalDiagonal) {
        if (ref == BoardMarks::X)
            return BoardState::XWins;
        else if (ref == BoardMarks::O)
            return BoardState::OWins;
    }

    // If there is an empty cell and no winner is determined, then the game is
    // still ongoing.
    for (int row = 0; row < this->boardSize; ++row)
        for (int col = 0; col < this->boardSize; ++col)
            if (board[row][col] == BoardMarks::Empty)
                return BoardState::NoWinner;

    // If no winner is determined and there are no empty cells, then the game is a
    // tie.
    return BoardState::Tie;
}

void Board::reset() {
    // Sets all the cells to empty.
    for (int row = 0; row < this->boardSize; ++row) {
        for (int col = 0; col < this->boardSize; ++col) {
            board[row][col] = BoardMarks::Empty;
        }
    }
}

int Board::size() const { return this->boardSize; }
