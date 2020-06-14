#ifndef BOARD_H
#define BOARD_H
#include<QtGlobal>

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
    BoardMarks AImark;
    BoardMarks playerMark;

private: // Methods
    int maxMove();
    int minMove();
    int score(BoardState state);

public:
    Board();
    BoardState evaluateBoard();
    bool setPlayerInput(int row, int col, BoardMarks currentPlayer);
    int miniMax(BoardMarks currentPlayer);
    BoardState updateState();
    void reset();
#ifdef QT_DEBUG
    void printBoard();
#endif
};

#endif // BOARD_H
