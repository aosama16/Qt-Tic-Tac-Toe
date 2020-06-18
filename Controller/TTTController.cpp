#include "TTTController.h"
#include "MiniMaxAgent.h"
#include "NoAgent.h"
#include "TicTacToeGame.h"
#include <QPushButton>

TTTController::TTTController(const TTTOptions &options, QObject *parent)
    : QObject(parent),
      view_(),
      board_(options.boardSize),
      options_(options),
      currentPlayer_(BoardMarks::X)
{
    // Build GUI
    cells_ = view_.buildCellButtons(options.boardSize);

    // Set Connections to the UI elements.
    setConnections();

    // Specifies the type of agent, and its behaviour throught polymorphism.
    if (options_.AIopponent && options_.AIstarts)
        agent_ = std::make_unique<MiniMaxAgent>(options_.miniMaxDepth, BoardMarks::X, BoardMarks::O);
    else if (options_.AIopponent)
        agent_ = std::make_unique<MiniMaxAgent>(options_.miniMaxDepth, BoardMarks::O, BoardMarks::X);
    else
        agent_ = std::make_unique<NoAgent>();

    // Setup a new game.
    reset();
}

void TTTController::startGame()
{
    // Shows the gameplay GUI.
    view_.exec();
}

void TTTController::setConnections()
{
    // Cell connections.
    for (Cell &cell : cells_)
        connect(cell.cellBtn, &QPushButton::clicked, [&] { updateGame(cell); });

    // New Game Connection - resetting the game.
    connect(&view_, &TicTacToeGame::newGame, this, [&] { reset(); });

    // Connect AI to play after a cell is chosen by human input.
    connect(this, &TTTController::turnFinished, [=] { AIAgentPlay(); });
}

void TTTController::updateGameState(Cell &cell)
{
    // Updates the cell view.
    this->view_.updateCell(cell, currentPlayer_);

#ifdef QT_DEBUG
    board_.printBoard();
#endif
    // Update board state and declare state if its a final state.
    BoardState boardState = board_.evaluateBoard();
    if (BoardState::NoWinner != boardState)
        view_.declareGameState(boardState);

    // Switch the players.
    switchPlayer();
}

void TTTController::reset()
{
    // Resets the current player back to X.
    currentPlayer_ = BoardMarks::X;
    // Resets the View GUI elements.
    view_.reset(cells_);
    // Resets the internal Representation of the board.
    board_.reset();
    // Resets the AI agent.
    // Uses the arrow operator to avoid calling unique_pointer::reset()
    agent_->reset();
    // Start AI play.
    if (options_.AIstarts)
        AIAgentPlay();
}

void TTTController::AIAgentPlay()
{
    int cellIdx = agent_->play(board_);
    if (defaults::INVALID_CELL != cellIdx)
        updateGameState(cells_.at(static_cast<size_t>(cellIdx)));
}

void TTTController::switchPlayer()
{
    if (BoardMarks::X == currentPlayer_)
        currentPlayer_ = BoardMarks::O;
    else if (BoardMarks::O == currentPlayer_)
        currentPlayer_ = BoardMarks::X;
}

void TTTController::updateGame(Cell &cell)
{
    bool success = board_.setPlayerInput(static_cast<size_t>(cell.row),
                                         static_cast<size_t>(cell.col),
                                         currentPlayer_);
    if (success) {
        updateGameState(cell);
        emit turnFinished();
    }
}
