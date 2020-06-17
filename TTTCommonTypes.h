#ifndef TTTCOMMONTYPES_H
#define TTTCOMMONTYPES_H
#include <cstddef>

class QPushButton;

namespace defaults
{
constexpr short INVALID_CELL = -1;
constexpr size_t DEFAULT_BOARD_SIZE = 3;
constexpr unsigned short DEFAULT_MINIMAX_DEPTH = 3;
constexpr unsigned short GUI_CELL_ROW_SPAN = 1;
constexpr unsigned short GUI_CELL_COLUMN_SPAN = 1;
constexpr char X_COLOR[] = "#455A64";
constexpr char O_COLOR[] = "#FF5722";
constexpr char DEFAULT_COLOR[] = "#FFF";
}
/**
 * @brief The Cell struct
 */
struct Cell
{
    QPushButton *cellBtn = nullptr;
    int row = defaults::INVALID_CELL;
    int col = defaults::INVALID_CELL;
    Cell(QPushButton *cellBtn, int row, int col)
        : cellBtn(cellBtn), row(row), col(col) {}
};

/**
 * @brief The TTTOptions struct
 */
struct TTTOptions
{
    size_t boardSize = defaults::DEFAULT_BOARD_SIZE;
    unsigned short miniMaxDepth = defaults::DEFAULT_MINIMAX_DEPTH;
    bool AIopponent = true;
    bool AIstarts = false;
};

/**
 * @brief The BoardMarks enum
 */
enum class BoardMarks { Empty, X, O };

/**
 * @brief The BoardState enum
 */
enum class BoardState { NoWinner, XWins, OWins, Tie };

#endif // TTTCOMMONTYPES_H
