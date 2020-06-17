#ifndef TITLESCREEN_H
#define TITLESCREEN_H
#include "TTTCommonTypes.h"
#include <QMainWindow>

namespace Ui {
class TitleScreen;
}

/**
 * @brief The TitleScreen class is responsible for the GUI of the title screen,
 * its main functionality is to gather game options set by the user,
 * then starting a game by creating a Tic Tac Toe controller with the user options.
 */

class TitleScreen final : public QMainWindow
{
    Q_OBJECT

public:
    explicit TitleScreen(QWidget *parent = nullptr);
    ~TitleScreen();

private:
    Ui::TitleScreen *ui;
    void setConnections();

    TTTOptions options_;
    // QWidget interface
    void closeEvent(QCloseEvent *event) override;

public slots:
    void updateBoardSize(int size);
    void updateSinglePlayer(bool checked);
    void updateTwoPlayers(bool checked);
    void updateAIstartsGame(bool checked);
    void updateMiniMaxDepth(int depth);
    void startGame();


signals:
    void exited();
};

#endif // TITLESCREEN_H
