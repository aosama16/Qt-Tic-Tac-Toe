#include "board.h"
#include <QDebug>
#include <QString>

Board::Board()
{
    // Sets all the cells to empty.
	for(int row = 0; row < BOARD_SIZE; ++row){
        for (int col = 0; col < BOARD_SIZE; ++col){
            board[row][col] = BoardMarks::Empty;
        }
    }
}

void Board::printBoard()
{
    QString board;
    for(int row = 0; row < BOARD_SIZE; ++row){
        for (int col = 0; col < BOARD_SIZE; ++col){
            board += QString::number(static_cast<int>(this->board[row][col]));
        }
        board += '\n';
    }
    qDebug().noquote() << board;
}

bool Board::setPlayerInput(int row, int col, BoardMarks currentPlayer)
{
    if(row >= this->BOARD_SIZE && row < 0)
        return false;

    if(col >= this->BOARD_SIZE && col < 0)
        return false;

    if(board[row][col] != BoardMarks::Empty)
        return false;

    this->board[row][col] = currentPlayer;

    return true;
}

void Board::reset()
{
    // Sets all the cells to empty.
    for(int row = 0; row < BOARD_SIZE; ++row){
        for (int col = 0; col < BOARD_SIZE; ++col){
            board[row][col] = BoardMarks::Empty;
        }
    }
}
