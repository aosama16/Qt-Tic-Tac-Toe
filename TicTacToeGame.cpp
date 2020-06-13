#include "TicTacToeGame.h"
#include "ui_TicTacToeGame.h"

TicTacToeGame::TicTacToeGame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TicTacToeGame)
{
    ui->setupUi(this);
}

TicTacToeGame::~TicTacToeGame()
{
    delete ui;
}
