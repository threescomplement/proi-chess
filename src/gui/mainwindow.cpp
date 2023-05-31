#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "ClickableLabel.h"
#include "GameField.h"
#include "../chess/Game.h"
#include "constants.h"
#include "Position.h"
#include "Move.h"
#include "pieces/Piece.h"
#include "pieces/PieceType.h"
#include <vector>

MainWindow::MainWindow(Game *game, QWidget *parent)
        : MainWindow(parent) {
    this->game = game;
    updateBoardDisplay();
}

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), game(nullptr), pickedField(nullptr) {
    ui->setupUi(this);
    QPixmap board_map(":/resources/Empty_Board.jpg");
    ui->GameBoard->setPixmap(board_map);

    for (int row = 1; row <= 8; row++) {
        for (int column = 1; column <= 8; column++) {
            auto *field = new GameField(QString("Nie kliknięte"), column, row, this);
            QObject::connect(this, &MainWindow::update_field, field, &GameField::update_called);
            QObject::connect(field, &GameField::fieldClicked, this, &MainWindow::handleFieldClick);
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

void MainWindow::handleFieldClick(GameField *field) {

    if (field != pickedField) {

        // check if there is a move to the chosen position
        Move *correspondingMove = findMove(validMoves, field);
        if (correspondingMove != nullptr) {
            makeMove(*correspondingMove);
            changePickedField(nullptr);
        } else {    // if not, pick the clicked field as the starting one
            changePickedField(field);
        }
    } else if (pickedField == nullptr) {
        changePickedField(field);
    }
    updateBoardDisplay();
}

Move *MainWindow::findMove(const std::vector<Move> &moves, const GameField *field) {
    Move *foundMove = nullptr;
    for (auto move: moves) {
        Position goal = move.getTo();
        if (goal.getCol() == field->getX() && goal.getRow() == field->getY()) {
            foundMove = &move;
            break;
        }
    }
    if (foundMove != nullptr){
        return new Move(*foundMove);
    } else {
        return nullptr;
    }

}

void MainWindow::makeMove(Move const move) {
    game->makeMove(move);
    updateBoardDisplay();
}

void MainWindow::changePickedField(GameField *const new_picked) {

    if (pickedField != nullptr) {
        // mark the previously picked field as not marked anymore
        emit update_field(pickedField->getX(), pickedField->getY(), pickedField->getPiece(), false);
        // TODO: create a function updating all marks/highlights here
    }
    if (new_picked != nullptr) { // if the new picked is a field
        validMoves = game->getMovesFrom(Position(new_picked->getY(), new_picked->getX()));
        // update the mark of the newly picked field
        emit update_field(new_picked->getX(), new_picked->getY(), new_picked->getPiece(), true);
        // TODO: create a function resetting all marks/highlights here
    } else {
        validMoves.clear();
    }


    pickedField = new_picked;
}
