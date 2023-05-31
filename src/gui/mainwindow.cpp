#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "clickable_label.h"
#include "GameField.h"
#include "../chess/Game.h"
#include "constants.h"
#include "Position.h"
#include "pieces/Piece.h"
#include "pieces/PieceType.h"

MainWindow::MainWindow(Game *game, QWidget *parent)
        : MainWindow(parent) {
    this->game = game;
    updateBoardDisplay();
}

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), game(nullptr) {
    ui->setupUi(this);
    QPixmap board_map(":/resources/Empty_Board.jpg");
    ui->GameBoard->setPixmap(board_map);
    //GameField *click_label = new GameField(QString("poczatkowy tekst"), this);
    //ui->GameLayout->addWidget(click_label);
    //click_label->setAlignment(Qt::AlignRight);
    //click_label->setGeometry(50, 100, 50, 50);
    //click_label->show();
    for (int row = 1; row <= 8; row++) {
        for (int column = 1; column <= 8; column++) {
            auto *field = new GameField(QString("Nie kliknięte"), column, row, this);
            QObject::connect(this, &MainWindow::update_field, field, &GameField::update_called);
            QObject::connect(field, &GameField::fieldClicked, this, &MainWindow::highlightNeighbours);
            field->setAlignment(Qt::AlignLeft);
            field->setGeometry(50 * column - 20, 50 * row + 20, 50, 50);
            field->show();
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
    delete game;
}

void MainWindow::move(int start_x, int start_y) {

}

void MainWindow::highlightNeighbours(int origin_x, int origin_y) {
    emit update_field(origin_x - 1, origin_y, PieceType::PAWN);
    emit update_field(origin_x, origin_y - 1, PieceType::PAWN);
    emit update_field(origin_x + 1, origin_y, PieceType::PAWN);
    emit update_field(origin_x, origin_y + 1, PieceType::PAWN);
}


void MainWindow::on_newGameButton_clicked() {

}

void MainWindow::updateBoardDisplay() {
    for (int row = 1; row <= BOARD_SIZE; row++) {
        for (int col = 1; col <= BOARD_SIZE; col++) {
            auto piece = this->game->getPiece(Position(row, col));
            auto type = (piece != nullptr) ? piece->getType() : PieceType::NONE;
            emit update_field(col, row, type);
        }
    }
}

