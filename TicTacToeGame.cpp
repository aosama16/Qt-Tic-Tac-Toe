#include <QMessageBox>
#include "TicTacToeGame.h"
#include "ui_TicTacToeGame.h"

TicTacToeGame::TicTacToeGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TicTacToeGame)
{
    ui->setupUi(this);

    currentPlayer = BoardMarks::X;

    setConnections();
}

TicTacToeGame::~TicTacToeGame()
{
    delete ui;
}

void TicTacToeGame::setConnections()
{
    // Cell connections
    connect(ui->cell_1, &QPushButton::clicked, [=] { cellClicked(ui->cell_1, 0, 0); });
    connect(ui->cell_2, &QPushButton::clicked, [=] { cellClicked(ui->cell_2, 0, 1); });
    connect(ui->cell_3, &QPushButton::clicked, [=] { cellClicked(ui->cell_3, 0, 2); });
    connect(ui->cell_4, &QPushButton::clicked, [=] { cellClicked(ui->cell_4, 1, 0); });
    connect(ui->cell_5, &QPushButton::clicked, [=] { cellClicked(ui->cell_5, 1, 1); });
    connect(ui->cell_6, &QPushButton::clicked, [=] { cellClicked(ui->cell_6, 1, 2); });
    connect(ui->cell_7, &QPushButton::clicked, [=] { cellClicked(ui->cell_7, 2, 0); });
    connect(ui->cell_8, &QPushButton::clicked, [=] { cellClicked(ui->cell_8, 2, 1); });
    connect(ui->cell_9, &QPushButton::clicked, [=] { cellClicked(ui->cell_9, 2, 2); });

    // New Game Connection - resetting the game
    connect(ui->reset, SIGNAL(clicked()), SLOT(reset()));
}

void TicTacToeGame::switchPlayer()
{
    if(this->currentPlayer == BoardMarks::X)
        this->currentPlayer = BoardMarks::O;
    else if (this->currentPlayer == BoardMarks::O)
        this->currentPlayer = BoardMarks::X;
}

QString TicTacToeGame::getCurrentPlayerText()
{
    switch (this->currentPlayer) {
    case BoardMarks::O: return "O";
    case BoardMarks::X: return "X";
    default : return "";
    }
}

QString TicTacToeGame::getCurrentPlayerColor()
{
    switch (this->currentPlayer) {
    case BoardMarks::O: return "#FF5722";
    case BoardMarks::X: return "#455A64";
    default : return "";
    }
}

QString TicTacToeGame::getBoardFinalStateText(BoardState boardState)
{
    switch (boardState) {
    case BoardState::XWins: return "Player X wins!";
    case BoardState::OWins: return "Player O wins!";
    case BoardState::Tie: return "It's a tie!";
    default : return "";
    }
}

void TicTacToeGame::declareGameState(BoardState boardState)
{
    QMessageBox resultBox;
    resultBox.setWindowTitle("Game Result");
    resultBox.setMinimumWidth(500);
    resultBox.setText("Game over, " + getBoardFinalStateText(boardState));
    resultBox.exec();
}

void TicTacToeGame::cellClicked(QPushButton* cell, int row, int col)
{
    bool success = board.setPlayerInput(row, col, this->currentPlayer);
    if(success){
        cell->setStyleSheet(QString("color: %1;").arg(getCurrentPlayerColor()));
        cell->setText(getCurrentPlayerText());
#ifdef QT_DEBUG
        board.printBoard();
#endif
        BoardState boardState = board.updateState(this->currentPlayer);
        if(boardState != BoardState::NoWinner){
            declareGameState(boardState);
        }
        switchPlayer();
    }
}

void TicTacToeGame::reset()
{
    // Resets the current player back to X
    currentPlayer = BoardMarks::X;

    // Resets the internal Representation of the board.
    board.reset();

    // Resets the GUI cells to an empty button with no text marks.
    ui->cell_1->setText("");
    ui->cell_2->setText("");
    ui->cell_3->setText("");
    ui->cell_4->setText("");
    ui->cell_5->setText("");
    ui->cell_6->setText("");
    ui->cell_7->setText("");
    ui->cell_8->setText("");
    ui->cell_9->setText("");
}
