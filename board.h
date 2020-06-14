#ifndef BOARD_H
#define BOARD_H
#include <QtGlobal>
#include <vector>

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

using std::vector;

class Board
{

private: // Data
    vector<vector<BoardMarks>>board;
    int boardSize;
    BoardMarks AImark;
    BoardMarks playerMark;

private: // Methods
    int maxMove();
    int minMove();
    int score(BoardState state);

public:
    Board(int boardSize);
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
