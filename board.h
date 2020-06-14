#ifndef BOARD_H
#define BOARD_H

enum class BoardMarks{
    Empty,
    X,
    O
};

enum class BoardState{
    NoWinner,
    XWins,
    OWins,
    Tie
};

class Board
{
private: // Data
    const static int BOARD_SIZE = 3;
    BoardMarks board[BOARD_SIZE][BOARD_SIZE];
    BoardState state;
    short inputCount;

private: // Methods
    BoardState getNewState(BoardMarks currentPlayer);

public:
    Board();
    void printBoard();
    bool setPlayerInput(int row, int col, BoardMarks currentPlayer);
    BoardState updateState(BoardMarks currentPlayer);
    void reset();
};

#endif // BOARD_H
