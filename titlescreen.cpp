#include "titlescreen.h"
#include "ui_titlescreen.h"

TitleScreen::TitleScreen(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TitleScreen), boardSize(3),
      miniMaxDepth(3), AIopponent(true), AIstarts(false) {
    ui->setupUi(this);
    setConnections();
}

void TitleScreen::setConnections() {
    connect(ui->boardSize, SIGNAL(valueChanged(int)), SLOT(updateBoardSize(int)));
    connect(ui->onePlayer, SIGNAL(toggled(bool)), SLOT(updateSinglePlayer(bool)));
    connect(ui->twoPlayers, SIGNAL(toggled(bool)), SLOT(updateTwoPlayers(bool)));
    connect(ui->AIStarts, SIGNAL(toggled(bool)), SLOT(updateAIstartsGame(bool)));
    connect(ui->miniMaxDepth, SIGNAL(valueChanged(int)),
            SLOT(updateMiniMaxDepth(int)));
    connect(ui->startGame, SIGNAL(clicked()), SLOT(startGame()));
}

void TitleScreen::updateBoardSize(int size) {
    ui->boardSizeValue->setText(QString::number(size));
    this->boardSize = size;
}

void TitleScreen::updateSinglePlayer(bool checked) {
    if (checked) {
        ui->AIStarts->setEnabled(true);
        ui->miniMaxDepth->setEnabled(true);
        this->AIopponent = true;
    }
}

void TitleScreen::updateTwoPlayers(bool checked) {
    if (checked) {
        ui->AIStarts->setEnabled(false);
        ui->miniMaxDepth->setEnabled(false);
        this->AIopponent = false;
    }
}

void TitleScreen::updateAIstartsGame(bool checked) {
    if (checked) {
        this->AIstarts = true;
    } else {
        this->AIstarts = false;
    }
}

void TitleScreen::updateMiniMaxDepth(int depth) {
    ui->miniMaxDepthValue->setText(QString::number(depth));
    this->miniMaxDepth = depth;
}

void TitleScreen::startGame() {
    this->hide();
    TicTacToeGame game(nullptr, this->boardSize, this->AIopponent, this->AIstarts,
                       this->miniMaxDepth);
    game.exec();
    this->show();
}

TitleScreen::~TitleScreen() { delete ui; }

void TitleScreen::closeEvent(QCloseEvent *event) {
    QMainWindow::closeEvent(event);
    emit exited();
}
