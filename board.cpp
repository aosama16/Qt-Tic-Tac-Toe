#include "board.h"
#include <QString>
#ifdef QT_DEBUG
#include <QDebug>
#endif

BoardState Board::getNewState(BoardMarks currentPlayer)
{
    // Sets possible new state based on the current player.
    BoardState newState = BoardState::NoWinner;
    if(currentPlayer == BoardMarks::X)
        newState = BoardState::XWins;
    else if (currentPlayer == BoardMarks::O)
        newState = BoardState::OWins;

    // Checks rows for a win for the current player.
    for(int row = 0; row < BOARD_SIZE; ++row)
        if(board[row][0] == currentPlayer &&
           board[row][1] == currentPlayer &&
           board[row][2] == currentPlayer )
            return newState;

    // Checks columns for a win for the current player.
    for(int col = 0; col < BOARD_SIZE; ++col)
        if(board[0][col] == currentPlayer &&
           board[1][col] == currentPlayer &&
           board[2][col] == currentPlayer )
            return newState;

    // Checks diagonals for a win for the current player.
    if(board[0][0] == currentPlayer &&
       board[1][1] == currentPlayer &&
       board[2][2] == currentPlayer )
        return newState;

    if(board[0][2] == currentPlayer &&
       board[1][1] == currentPlayer &&
       board[2][0] == currentPlayer )
        return newState;

    // If all the cells are filled and no winner is determined,
    // then the new state is a tie.
    if(this->inputCount == this->BOARD_SIZE * this->BOARD_SIZE)
        return BoardState::Tie;

    // If none of the other states are determined then the game is still ongoing.
    return BoardState::NoWinner;
}

Board::Board() :
    state(BoardState::NoWinner),
    inputCount(0)
{
    // Sets all the cells to empty.
	for(int row = 0; row < BOARD_SIZE; ++row){
        for (int col = 0; col < BOARD_SIZE; ++col){
            board[row][col] = BoardMarks::Empty;
        }
    }
}

#ifdef QT_DEBUG
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
#endif

bool Board::setPlayerInput(int row, int col, BoardMarks currentPlayer)
{
    // The game is over, so no input is allowed untill game resets.
    if(state != BoardState::NoWinner)
        return false;

    // Row input in not valid.
    if(row >= this->BOARD_SIZE && row < 0)
        return false;

    // Column input is not valid.
    if(col >= this->BOARD_SIZE && col < 0)
        return false;

    // Cell is not empty.
    if(board[row][col] != BoardMarks::Empty)
        return false;

    // Update cell with current player's mark.
    this->board[row][col] = currentPlayer;
    // Increase the count of inputs to help in detecting a Tie state.
    ++this->inputCount;

    return true;
}

int Board::getAIcellIdxInput(BoardMarks currentPlayer)
{
    if(state != BoardState::NoWinner)
        return -1;

    for(int row = 0; row < BOARD_SIZE; ++row){
        for (int col = 0; col < BOARD_SIZE; ++col){
            if(board[row][col] == BoardMarks::Empty){
                board[row][col] = currentPlayer;
                ++this->inputCount;
                return row * this->BOARD_SIZE + col;
            }
        }
    }
    return -1;
}

BoardState Board::updateState(BoardMarks currentPlayer)
{
    // Updates the state with the new state and returns it to the game.
    return this->state = getNewState(currentPlayer);
}

void Board::reset()
{
    // Resets the state to the default state - No Winner
    state = BoardState::NoWinner;
    // Resets the input count
    inputCount = 0;

    // Sets all the cells to empty.
    for(int row = 0; row < BOARD_SIZE; ++row){
        for (int col = 0; col < BOARD_SIZE; ++col){
            board[row][col] = BoardMarks::Empty;
        }
    }
}
