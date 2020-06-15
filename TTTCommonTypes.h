#ifndef TTTCOMMONTYPES_H
#define TTTCOMMONTYPES_H

class QPushButton;

struct Cell {
    QPushButton *cellBtn = nullptr;
    int row = -1;
    int col = -1;
    Cell(QPushButton *cellBtn, int row, int col)
        : cellBtn(cellBtn), row(row), col(col) {}
};

struct TTTOptions {
    int boardSize = 3;
    int miniMaxDepth = 3;
    bool AIopponent = true;
    bool AIstarts = false;
};

enum class BoardMarks { Empty, X, O };

enum class BoardState { NoWinner, XWins, OWins, Tie };

#endif // TTTCOMMONTYPES_H
