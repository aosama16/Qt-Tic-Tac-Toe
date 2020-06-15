#include "TicTacToeGame.h"

#include <QDebug>
#include <QMessageBox>

#include "ui_TicTacToeGame.h"

TicTacToeGame::TicTacToeGame(QWidget *parent, int boardSize, bool AIopponent,
                             bool AIstarts, int miniMaxDepth)
    : QDialog(parent), ui(new Ui::TicTacToeGame), board(boardSize),
      AIopponent(AIopponent), startWithAI(AIstarts),
      miniMaxDepth(miniMaxDepth) {
    ui->setupUi(this);

    currentPlayer = BoardMarks::X;

    buildCellButtons(boardSize);

    setConnections();

    // Setup a new game
    reset();
}

TicTacToeGame::~TicTacToeGame() { delete ui; }

void TicTacToeGame::buildCellButtons(int boardSize) {
    cells.reserve(boardSize * boardSize);
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            // Add buttons to gridLayout
            QPushButton *btn = new QPushButton();
            btn->setProperty("cell", true);
            ui->gridBoard->addWidget(btn, row, col, 1, 1);
            // Reference to cells
            cells.emplace_back(btn, row, col);
        }
    }
}

void TicTacToeGame::setConnections() {
    // Cell connections
    for (Cell &cell : this->cells)
        connect(cell.cellBtn, &QPushButton::clicked, [&] { cellClicked(cell); });

    // New Game Connection - resetting the game
    connect(ui->reset, SIGNAL(clicked()), SLOT(reset()));

    // Connect AI to play after a cell is chosen by human input
    if (this->AIopponent)
        connect(this, SIGNAL(turnFinished()), this, SLOT(playAIturn()));

    connect(ui->back, SIGNAL(clicked(bool)), SLOT(backToTitle()));
}

void TicTacToeGame::switchPlayer() {
    if (this->currentPlayer == BoardMarks::X)
        this->currentPlayer = BoardMarks::O;
    else if (this->currentPlayer == BoardMarks::O)
        this->currentPlayer = BoardMarks::X;
}

QString TicTacToeGame::getCurrentPlayerText() {
    switch (this->currentPlayer) {
    case BoardMarks::O:
        return "O";
    case BoardMarks::X:
        return "X";
    default:
        return "";
    }
}

QString TicTacToeGame::getCurrentPlayerStyleSheet() {
    QString color;

    switch (this->currentPlayer) {
    case BoardMarks::O:
        color = "#FF5722";
        break;
    case BoardMarks::X:
        color = "#455A64";
        break;
    default:
        return "#FFF";
    }

    return QString("font: 50px \"Verdana\";"
                   "min-height: 100px;"
                   "max-height: 100px;"
                   "min-width: 100px;"
                   "max-width: 100px;"
                   "color: %1")
        .arg(color);
}

QString TicTacToeGame::getBoardFinalStateText(BoardState boardState) {
    switch (boardState) {
    case BoardState::XWins:
        return "Player X wins!";
    case BoardState::OWins:
        return "Player O wins!";
    case BoardState::Tie:
        return "It's a tie!";
    default:
        return "";
    }
}

void TicTacToeGame::playAIturn() {
    int cellIdx = board.miniMax(this->currentPlayer, this->miniMaxDepth);
    if (cellIdx != -1)
        updateGameState(cells.at(cellIdx));
}

void TicTacToeGame::declareGameState(BoardState boardState) {
    QMessageBox resultBox;
    resultBox.setWindowTitle("Game Result");
    resultBox.setText("Game over, " + getBoardFinalStateText(boardState));
    resultBox.exec();
}

void TicTacToeGame::updateGameState(Cell &cell) {
    // Update Cell button in GUI
    cell.cellBtn->setStyleSheet(getCurrentPlayerStyleSheet());
    cell.cellBtn->setText(getCurrentPlayerText());

#ifdef QT_DEBUG
    board.printBoard();
#endif
    // Update board state and declare state if its a final state
    BoardState boardState = board.evaluateBoard();
    if (boardState != BoardState::NoWinner)
        declareGameState(boardState);

    // Switch the players
    switchPlayer();
}

void TicTacToeGame::cellClicked(Cell &cell) {
    bool success = board.setPlayerInput(cell.row, cell.col, this->currentPlayer);
    if (success) {
        updateGameState(cell);
        emit turnFinished();
    }
}

void TicTacToeGame::reset() {
    // Resets the current player back to X
    currentPlayer = BoardMarks::X;

    // Resets the internal Representation of the board.
    board.reset();

    // Resets the GUI cells to an empty button with no text marks.
    for (auto &cell : cells)
        cell.cellBtn->setText("");

    if (this->AIopponent && this->startWithAI)
        playAIturn();
}

void TicTacToeGame::backToTitle() { this->close(); }
