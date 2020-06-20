#ifndef TITLESCREEN_H
#define TITLESCREEN_H
#include "TTTCommonTypes.h"
#include "ui_titlescreen.h"
#include <QMainWindow>
#include <memory>

/**
 * @brief The TitleScreen class is responsible for the GUI of the title screen,
 * its main functionality is to gather game options set by the user,
 * then starting a game by creating a Tic Tac Toe controller with the user options.
 */

class TitleScreen final : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief TitleScreen constructs the view of the title screen.
     * @param parent is a QWidget type parent that owns this instance of the controller.
     */
    explicit TitleScreen(QWidget *parent = nullptr);

private:
    /**
     * @brief ui is a reference to the ui object of the tic tac toe game.
     */
    std::unique_ptr<Ui::TitleScreen> ui;
    /**
     * @brief setConnections sets connections to gather game options from the GUI elements.
     */
    void setConnections();
    /**
     * @brief options are the values and flags that control a tic tac toe game.
     */
    TTTOptions options_;
    /**
     * @brief closeEvent manually handles the closing event defined in the base class QWidget.
     * @param event: the closing event.
     */
    void closeEvent(QCloseEvent *event) override;

public slots:
    /**
     * @brief updateBoardSize updates the board size in the current options.
     * @param size: the number of rows or columns in the board.
     */
    void updateBoardSize(int size);
    /**
     * @brief updateSinglePlayer updates the AI existence flag to true as there is one player.
     * @param checked: wether the radio button is checked or not.
     */
    void updateSinglePlayer(bool checked);
    /**
     * @brief updateTwoPlayers updates the AI existence flag to false as there are two player.
     * @param checked: wether the radio button is checked or not.
     */
    void updateTwoPlayers(bool checked);
    /**
     * @brief updateAIstartsGame sets the AI starting the first play or not.
     * @param checked: wether the checkbox is checked or not.
     */
    void updateAIstartsGame(bool checked);
    /**
     * @brief updateMiniMaxDepth sets the value of the depth cutoff for the minimax algorithm.
     * @param depth: the depth cutoff for the minimax algorithm.
     */
    void updateMiniMaxDepth(int depth);
    /**
     * @brief startGame hides the title screen and creates a Tic tac toe controller to start a game.
     */
    void startGame();


signals:
    /**
     * @brief exited is emitted to manually handle the close functionality.
     */
    void exited();
};

#endif // TITLESCREEN_H
