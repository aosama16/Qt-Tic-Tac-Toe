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
 * @brief The TTTController class is the controller for a Tic Tac Toe game,
 * it takes in game options as input, and controls the view (TicTacToeGame)
 * and the model (Board) according to the game logic specified in this class,
 * it is also responsible for calling the AI agent to play its turn if specified
 * by the game options.
 */

class TTTController : public QObject
{
    Q_OBJECT
protected:
    /**
     * @brief view is the view class of a tic tac toe game.
     */
    TicTacToeGame view_;
    /**
     * @brief board is the model that represents the underlying layer of a game.
     */
    Board board_;
    /**
     * @brief cells are the collection of cell buttons built by the view class.
     */
    vector<Cell> cells_;
    /**
     * @brief options is the collection of values and flags that controls the game.
     */
    const TTTOptions& options_;
    /**
     * @brief currentPlayer is the player that will play the current turn.
     */
    BoardMarks currentPlayer_;
    /**
     * @brief agent is the AI agent chosen to play against the human player.
     */
    unique_ptr<AIAgent> agent_;

private: // Methods
    /**
     * @brief setConnections will set a connection to all GUI elements to slots defined
     * to handle these events.
     */
    void setConnections();
    /**
     * @brief resets all internal components, the view, the model and the AI agent.
     * then if AI is supposed to start a game it will play first.
     */
    void reset();

protected: // Methods
    /**
     * @brief updateGameState updates the view and the model and switches the current player.
     * @param cell: the clicked cell that the player chooses.
     */
    virtual void updateGameState(Cell &cell);
    /**
     * @brief AIAgentPlay calls the AI agent to play given the current board inputs.
     */
    virtual void AIAgentPlay();
    /**
     * @brief switchPlayer switches the current player mark (X to O and O to X).
     */
    virtual void switchPlayer();

public:
    /**
     * @brief TTTController constructs a game controller.
     * @param options is the collection of values and flags that controls the game.
     * @param parent is a QObject type parent that owns this instance of the controller.
     */
    explicit TTTController(const TTTOptions &options, QObject *parent = nullptr);
    /**
     * @brief startGame executes this QDialog to show the GUI and start the gameplay.
     */
    virtual void startGame();

signals:
    /**
     * @brief turnFinished is emitted when the human player is finished with the cell input,
     * and the internal game state is supposed to be updated.
     */
    void turnFinished();

public slots:
    /**
     * @brief updateGame sets the cell clicked in the model (board).
     * @param cell: the clicked cell that the player chooses.
     */
    virtual void updateGame(Cell &cell);
};

#endif // TTTCONTROLLER_H
