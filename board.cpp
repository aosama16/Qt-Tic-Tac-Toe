#include "board.h"
#include <QDebug>
#include <QString>

Board::Board()
{
	for(int row = 0; row < BOARD_SIZE; ++row){
        for (int col = 0; col < BOARD_SIZE; ++col){
            board[row][col] = BoardMarks::Empty;
        }
    }

}
