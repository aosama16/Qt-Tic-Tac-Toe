#include "TicTacToeGame.h"
#include "ui_TicTacToeGame.h"
#include <QMessageBox>
#include <QPushButton>

TicTacToeGame::TicTacToeGame(QWidget *parent)
    : QDialog(parent), ui(new Ui::TicTacToeGame)
{
    ui->setupUi(this);
    setConnections();
}

TicTacToeGame::~TicTacToeGame()
{
    delete ui;
}

void TicTacToeGame::setConnections()
{
    // New Game Connection - resetting the game
    connect(ui->reset, &QPushButton::clicked, [=] { emit newGame(); });
    connect(ui->back, &QPushButton::clicked, [=] { close(); });
}

vector<Cell> TicTacToeGame::buildCellButtons(int boardSize)
{
    vector<Cell> cells;
    cells.reserve(boardSize * boardSize);
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            // Add buttons to gridLayout
            QPushButton *btn = new QPushButton();
            btn->setProperty("cell", true);
            ui->gridBoard->addWidget(btn, row, col, defaults::GUI_CELL_ROW_SPAN, defaults::GUI_CELL_COLUMN_SPAN);
            // Reference to cells
            cells.emplace_back(btn, row, col);
        }
    }
    // Adjusts wnindow size to fit children widgets added dynamically
    adjustSize();

    // Return by value to allow for RVO (Copy Ellision)
    return cells;
}

QString TicTacToeGame::getPlayerText(BoardMarks currentPlayer)
{
    switch (currentPlayer) {
    case BoardMarks::O:
        return "O";
    case BoardMarks::X:
        return "X";
    default:
        return "";
    }
}

QString TicTacToeGame::getPlayerStyleSheet(BoardMarks currentPlayer)
{
    QString color;

    switch (currentPlayer) {
    case BoardMarks::O:
        color = defaults::O_COLOR;
        break;
    case BoardMarks::X:
        color = defaults::X_COLOR;
        break;
    default:
        color = defaults::DEFAULT_COLOR;
        break;
    }

    return QString("font: 50px \"Verdana\";"
                   "min-height: 100px;"
                   "max-height: 100px;"
                   "min-width: 100px;"
                   "max-width: 100px;"
                   "color: %1")
        .arg(color);
}

void TicTacToeGame::updateCell(Cell &cell, BoardMarks currentPlayer)
{
    // Update Cell button in GUI
    cell.cellBtn->setStyleSheet(getPlayerStyleSheet(currentPlayer));
    cell.cellBtn->setText(getPlayerText(currentPlayer));
}

QString TicTacToeGame::getBoardFinalStateText(BoardState boardState)
{
    switch (boardState) {
    case BoardState::XWins:
        return "player X wins!";
    case BoardState::OWins:
        return "player O wins!";
    case BoardState::Tie:
        return "it's a tie!";
    default:
        return "";
    }
}

void TicTacToeGame::declareGameState(BoardState boardState)
{
    QMessageBox resultBox;
    resultBox.setWindowTitle("Game Result");
    resultBox.setText("Game over, " + getBoardFinalStateText(boardState));
    resultBox.exec();
}

void TicTacToeGame::reset(vector<Cell> &cells)
{
    // Resets the GUI cells to an empty button with no text marks.
    for (auto &cell : cells)
        cell.cellBtn->setText("");
}
