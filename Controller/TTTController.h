#ifndef TTTCONTROLLER_H
#define TTTCONTROLLER_H
#include "AIAgent.h"
#include "Board.h"
#include "TTTCommonTypes.h"
#include "TicTacToeGame.h"
#include <QObject>
#include <memory>
#include <vector>

using std::unique_ptr;
using std::vector;

/**
 * @brief The TTTController classis the controller for a Tic Tac Toe game,
 * it takes in game options as input, and controls the view (TicTacToeGame)
 * and the model (Board) according to the game logic specified in this class,
 * it is also responsible for calling the AI agent to play its turn if specified
 * by the game options.
 */

class TTTController : public QObject
{
    Q_OBJECT
protected:
    // View
    TicTacToeGame view_;
    // Model
    Board board_;
    // Cells built by the view
    vector<Cell> cells_;
    // Game Logic Variables
    const TTTOptions& options_;
    BoardMarks currentPlayer_;
    unique_ptr<AIAgent> agent_;

private: // Methods
    void setConnections();
    void reset();

protected: // Methods
    virtual void updateGameState(Cell &cell);
    virtual void AIAgentPlay();
    virtual void switchPlayer();

public:
    explicit TTTController(const TTTOptions &options, QObject *parent = nullptr);
    virtual void startGame();

signals:
    void turnFinished();

public slots:
    virtual void updateGame(Cell &cell);
};

#endif // TTTCONTROLLER_H
