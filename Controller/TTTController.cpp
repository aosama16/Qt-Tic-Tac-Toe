#include "TTTController.h"
#include "MiniMaxAgent.h"
#include "NoAgent.h"
#include "TicTacToeGame.h"
#include <QPushButton>

TTTController::TTTController(TTTOptions &options, QObject *parent)
    : QObject(parent), view(), board(options.boardSize), options(options),
      currentPlayer(BoardMarks::X) {
    cells = view.buildCellButtons(options.boardSize);
    setConnections();

    if (this->options.AIopponent)
        agent = std::make_unique<MiniMaxAgent>(this->options.miniMaxDepth);
    else
        agent = std::make_unique<NoAgent>();

    // Setup a new game
    reset();
}

void TTTController::startGame() { view.exec(); }

void TTTController::setConnections() {
    // Cell connections
    for (Cell &cell : this->cells)
        connect(cell.cellBtn, &QPushButton::clicked, [&] { updateGame(cell); });

    // New Game Connection - resetting the game
    connect(&view, &TicTacToeGame::newGame, this, [&] { reset(); });

    // Connect AI to play after a cell is chosen by human input
    connect(this, &turnFinished, [=] { AIAgentPlay(); });
}

void TTTController::updateGameState(Cell &cell) {

    this->view.updateCell(cell, this->currentPlayer);

#ifdef QT_DEBUG
    board.printBoard();
#endif
    // Update board state and declare state if its a final state
    BoardState boardState = board.evaluateBoard();
    if (boardState != BoardState::NoWinner)
        this->view.declareGameState(boardState);

    // Switch the players
    switchPlayer();
}

void TTTController::reset() {
    // Resets the current player back to X
    currentPlayer = BoardMarks::X;
    // Resets the View GUI elements.
    view.reset(this->cells);
    // Resets the internal Representation of the board.
    board.reset();
    // Start AI play
    if (this->options.AIstarts)
        AIAgentPlay();
}

void TTTController::AIAgentPlay() {
    int cellIdx = agent->play(this->board, this->currentPlayer);
    if (cellIdx != -1)
        updateGameState(cells.at(cellIdx));
}

void TTTController::switchPlayer() {
    if (this->currentPlayer == BoardMarks::X)
        this->currentPlayer = BoardMarks::O;
    else if (this->currentPlayer == BoardMarks::O)
        this->currentPlayer = BoardMarks::X;
}

void TTTController::updateGame(Cell &cell) {
    bool success = board.setPlayerInput(cell.row, cell.col, this->currentPlayer);
    if (success) {
        updateGameState(cell);
        emit turnFinished();
    }
}
