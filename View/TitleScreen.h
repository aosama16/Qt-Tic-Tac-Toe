#ifndef TITLESCREEN_H
#define TITLESCREEN_H
#include "TTTCommonTypes.h"
#include <QMainWindow>

namespace Ui {
class TitleScreen;
}

class TitleScreen final : public QMainWindow {
    Q_OBJECT

public:
    explicit TitleScreen(QWidget *parent = nullptr);
    ~TitleScreen();

private:
    Ui::TitleScreen *ui;
    void setConnections();

    TTTOptions options;

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
