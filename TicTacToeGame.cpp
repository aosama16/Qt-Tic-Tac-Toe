#include <QMessageBox>
#include "TicTacToeGame.h"
#include "ui_TicTacToeGame.h"

TicTacToeGame::TicTacToeGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TicTacToeGame)
{
    ui->setupUi(this);

    currentPlayer = BoardMarks::X;
    AIopponent = false;
    startWithAI = true;

    // Reference to cells
    cells.reserve(9);
    cells.emplace_back(ui->cell_1, 0, 0);
    cells.emplace_back(ui->cell_2, 0, 1);
    cells.emplace_back(ui->cell_3, 0, 2);
    cells.emplace_back(ui->cell_4, 1, 0);
    cells.emplace_back(ui->cell_5, 1, 1);
    cells.emplace_back(ui->cell_6, 1, 2);
    cells.emplace_back(ui->cell_7, 2, 0);
    cells.emplace_back(ui->cell_8, 2, 1);
    cells.emplace_back(ui->cell_9, 2, 2);

    setConnections();

    // Setup a new game
    reset();
}

TicTacToeGame::~TicTacToeGame()
{
    delete ui;
}

void TicTacToeGame::setConnections()
{
    // Cell connections
    for(Cell& cell: this->cells)
        connect(cell.cellBtn, &QPushButton::clicked, [&] { cellClicked(cell); });

    // New Game Connection - resetting the game
    connect(ui->reset, SIGNAL(clicked()), SLOT(reset()));

    // Connect AI to play after a cell is chosen by human input
    if(this->AIopponent)
        connect(this, SIGNAL(turnFinished()), this, SLOT(playAIturn()));
}

void TicTacToeGame::switchPlayer()
{
    if(this->currentPlayer == BoardMarks::X)
        this->currentPlayer = BoardMarks::O;
    else if (this->currentPlayer == BoardMarks::O)
        this->currentPlayer = BoardMarks::X;
}

QString TicTacToeGame::getCurrentPlayerText()
{
    switch (this->currentPlayer) {
    case BoardMarks::O: return "O";
    case BoardMarks::X: return "X";
    default : return "";
    }
}

QString TicTacToeGame::getCurrentPlayerColor()
{
    switch (this->currentPlayer) {
    case BoardMarks::O: return "#FF5722";
    case BoardMarks::X: return "#455A64";
    default : return "";
    }
}

QString TicTacToeGame::getBoardFinalStateText(BoardState boardState)
{
    switch (boardState) {
    case BoardState::XWins: return "Player X wins!";
    case BoardState::OWins: return "Player O wins!";
    case BoardState::Tie: return "It's a tie!";
    default : return "";
    }
}

void TicTacToeGame::playAIturn()
{
    int cellIdx = board.getAIcellIdxInput(this->currentPlayer);
    if(cellIdx != -1)
        updateGameState(cells.at(cellIdx));
}

void TicTacToeGame::declareGameState(BoardState boardState)
{
    QMessageBox resultBox;
    resultBox.setWindowTitle("Game Result");
    resultBox.setText("Game over, " + getBoardFinalStateText(boardState));
    resultBox.exec();
}

void TicTacToeGame::updateGameState(Cell& cell)
{
    // Update Cell button in GUI
    cell.cellBtn->setStyleSheet(QString("color: %1;").arg(getCurrentPlayerColor()));
    cell.cellBtn->setText(getCurrentPlayerText());

#ifdef QT_DEBUG
    board.printBoard();
#endif
    // Update board state and declare state if its a final state
    BoardState boardState = board.updateState(this->currentPlayer);
    if(boardState != BoardState::NoWinner)
        declareGameState(boardState);

    // Switch the players
    switchPlayer();
}

void TicTacToeGame::cellClicked(Cell& cell)
{
    bool success = board.setPlayerInput(cell.row, cell.col, this->currentPlayer);
    if(success){
        updateGameState(cell);
        emit turnFinished();
    }
}

void TicTacToeGame::reset()
{
    // Resets the current player back to X
    currentPlayer = BoardMarks::X;

    // Resets the internal Representation of the board.
    board.reset();

    // Resets the GUI cells to an empty button with no text marks.
    for(auto& cell : cells)
        cell.cellBtn->setText("");

    if(this->AIopponent && this->startWithAI)
        playAIturn();
}
