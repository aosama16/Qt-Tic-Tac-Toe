#ifndef TTTCONTROLLER_H
#define TTTCONTROLLER_H
#include "tttcommontypes.h"
#include "TicTacToeGame.h"
#include "board.h"
#include <vector>
#include <QObject>

using std::vector;

class TTTController : public QObject
{
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
