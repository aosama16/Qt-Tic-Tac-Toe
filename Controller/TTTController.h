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

class TTTController : public QObject {
    Q_OBJECT
protected:
    // View
    TicTacToeGame view;
    // Model
    Board board;
    // Cells built by the view
    vector<Cell> cells;
    // Game Logic Variables
    const TTTOptions& options;
    BoardMarks currentPlayer;
    unique_ptr<AIAgent> agent;

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
