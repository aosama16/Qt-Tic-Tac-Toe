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
private:
    // View
    TicTacToeGame view;
    // Model
    Board board;

    // Cells built by the view
    vector<Cell> cells;
    // Game Logic Variables
    TTTOptions options;
    BoardMarks currentPlayer;
    unique_ptr<AIAgent> agent;

private: // Methods
    void setConnections();
    void updateGameState(Cell &cell);
    void reset();
    void AIAgentPlay();
    void switchPlayer();

public:
    explicit TTTController(TTTOptions &options, QObject *parent = nullptr);
    void startGame();

signals:
    void turnFinished();

public slots:
    void updateGame(Cell &cell);
};

#endif // TTTCONTROLLER_H
