#ifndef BOARD_H
#define BOARD_H

enum class BoardMarks{
    Empty,
    X,
    O
};

class Board
{
private:
    const static int BOARD_SIZE = 3;
    BoardMarks board[BOARD_SIZE][BOARD_SIZE];
public:
    Board();
};

#endif // BOARD_H