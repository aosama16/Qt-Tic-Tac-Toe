#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <QMainWindow>
#include "TicTacToeGame.h"

namespace Ui {
class TitleScreen;
}

class TitleScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit TitleScreen(QWidget *parent = nullptr);
    ~TitleScreen();

private:
    Ui::TitleScreen *ui;
    void setConnections();

    int boardSize;
    int miniMaxDepth;
    bool AIopponent;
    bool AIstarts;

public slots:
    void updateBoardSize(int size);
    void updateSinglePlayer(bool checked);
    void updateTwoPlayers(bool checked);
    void updateAIstartsGame(bool checked);
    void updateMiniMaxDepth(int depth);
    void startGame();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void exited();
};

#endif // TITLESCREEN_H
