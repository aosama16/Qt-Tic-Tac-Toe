#include "board.h"
#include <QString>
#include <QPair>
#ifdef QT_DEBUG
#include <QDebug>
#endif



Board::Board()
{
    // Sets all the cells to empty.
	for(int row = 0; row < BOARD_SIZE; ++row){
        for (int col = 0; col < BOARD_SIZE; ++col){
            board[row][col] = BoardMarks::Empty;
        }
    }

    AImark = BoardMarks::Empty;
    playerMark = BoardMarks::Empty;
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
    if(evaluateBoard() != BoardState::NoWinner)
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

    return true;
}

BoardState Board::evaluateBoard()
{
    // Checks rows for a win for the current player.
    for(int row = 0; row < BOARD_SIZE; ++row){
        if(board[row][0] == board[row][1] &&
           board[row][1] == board[row][2] ){
            if (board[row][0] == BoardMarks::X)
                return BoardState::XWins;
            else if (board[row][0] == BoardMarks::O)
                return BoardState::OWins;
        }
    }

    // Checks columns for a win for the current player.
    for(int col = 0; col < BOARD_SIZE; ++col){
        if(board[0][col] == board[1][col] &&
           board[1][col] == board[2][col] ){
            if (board[0][col] == BoardMarks::X)
                return BoardState::XWins;
            else if (board[0][col] == BoardMarks::O)
                return BoardState::OWins;
        }
    }

    // Checks diagonals for a win for the current player.
    if(board[0][0] == board[1][1] &&
       board[1][1] == board[2][2] ){
        if (board[0][0] == BoardMarks::X)
            return BoardState::XWins;
        else if (board[0][0] == BoardMarks::O)
            return BoardState::OWins;
    }

    if(board[0][2] == board[1][1] &&
       board[1][1] == board[2][0] ){
        if (board[0][2] == BoardMarks::X)
            return BoardState::XWins;
        else if (board[0][2] == BoardMarks::O)
            return BoardState::OWins;
    }

    // If all the cells are filled and no winner is determined,
    // then the new state is a tie.
    short emptyCellsCount = 0;
    for(int row = 0; row < BOARD_SIZE; ++row)
        for (int col = 0; col < BOARD_SIZE; ++col)
            if(board[row][col] == BoardMarks::Empty)
                ++emptyCellsCount;
    if(emptyCellsCount == 0)
        return BoardState::Tie;

    // If none of the other states are determined then the game is still ongoing.
    return BoardState::NoWinner;
}

void Board::reset()
{
    // Sets all the cells to empty.
    for(int row = 0; row < BOARD_SIZE; ++row){
        for (int col = 0; col < BOARD_SIZE; ++col){
            board[row][col] = BoardMarks::Empty;
        }
    }

    AImark = BoardMarks::Empty;
    playerMark = BoardMarks::Empty;
}

int Board::score(BoardState state)
{
    if (AImark == BoardMarks::O && state == BoardState::OWins)
        return 1;
    else if (AImark == BoardMarks::X && state == BoardState::XWins)
        return 1;
    else if (AImark == BoardMarks::O && state == BoardState::XWins)
        return -1;
    else if (AImark == BoardMarks::X && state == BoardState::OWins)
        return -1;
    else
        return 0;
}

int Board::miniMax(BoardMarks currentPlayer)
{
    if(evaluateBoard() != BoardState::NoWinner)
        return -1;

    if(AImark == BoardMarks::Empty){
        AImark = currentPlayer;
        playerMark = (this->AImark == BoardMarks::O ? BoardMarks::X : BoardMarks::O);
    }

    int bestScore = INT_MIN;
    QPair<int, int> bestEntry;
    for(int row = 0; row < BOARD_SIZE; ++row){
        for (int col = 0; col < BOARD_SIZE; ++col){
            if(board[row][col] == BoardMarks::Empty){
                // Try the move
                board[row][col] = AImark;

                int moveScore = minMove();
                if(moveScore > bestScore){
                    bestScore = moveScore;
                    bestEntry.first = row;;
                    bestEntry.second = col;
                }

                // Reset the move done
                board[row][col] = BoardMarks::Empty;
            }
        }
    }

    board[bestEntry.first][bestEntry.second] = currentPlayer;
    return bestEntry.first * this->BOARD_SIZE + bestEntry.second;
}

int Board::maxMove()
{
    // if game over return score
    BoardState state = evaluateBoard();
    if(state != BoardState::NoWinner)
        return score(state);

    int bestScore = INT_MIN;
    for(int row = 0; row < BOARD_SIZE; ++row){
        for (int col = 0; col < BOARD_SIZE; ++col){
            if(board[row][col] == BoardMarks::Empty){
                // Try the move
                board[row][col] = this->AImark;

                // Compare result of this move with respect to AI
                bestScore = std::max(bestScore, minMove());

                // Reset the move done
                board[row][col] = BoardMarks::Empty;
            }
        }
    }
    return bestScore;
}

int Board::minMove()
{
    // if game over return score
    BoardState state = evaluateBoard();
    if(state != BoardState::NoWinner)
        return score(state);

    int bestScore = INT_MAX;
    for(int row = 0; row < BOARD_SIZE; ++row){
        for (int col = 0; col < BOARD_SIZE; ++col){
            if(board[row][col] == BoardMarks::Empty){
                // Try the move
                board[row][col] = playerMark;

                // Compare result of this move with respect to player
                bestScore = std::min(bestScore, maxMove());

                // Reset the move done
                board[row][col] = BoardMarks::Empty;
            }
        }
    }
    return bestScore;
}

