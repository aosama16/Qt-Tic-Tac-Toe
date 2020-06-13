#include "TicTacToeGame.h"
#include "ui_TicTacToeGame.h"

TicTacToeGame::TicTacToeGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TicTacToeGame)
{
    ui->setupUi(this);

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

void TicTacToeGame::cellClicked(QPushButton* cell, int row, int col)
{
    Q_UNUSED(row);
    Q_UNUSED(col);
    cell->setStyleSheet(QString("color: %1;").arg(getCurrentPlayerColor()));
    cell->setText(getCurrentPlayerText());
    switchPlayer();
}
