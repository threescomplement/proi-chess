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


/**
 * displays the image of a board,
 * then sets up a 8 x 8 grid of @class GameField
 * to act as clickable tiles on the board.
 * Connects the appropriate signals between the fields and the window
 *
 *
 *
 * @param game - the game that will be played and displayed in the window
 * @param parent
 */
MainWindow::MainWindow(Game *game, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), game(game), pickedField(nullptr) {
    ui->setupUi(this);
    QPixmap board_map(":/resources/symmetrical_empty_board.jpg");
    ui->GameBoard->setPixmap(board_map);

    for (int row = 1; row <= 8; row++) {
        for (int column = 1; column <= 8; column++) {
            auto *field = new GameField(QString("Nie kliknięte"), column, 9 - row, ui->GameBoard);
            QObject::connect(this, &MainWindow::updateFieldPiece, field, &GameField::updatePieceCalled);
            QObject::connect(field, &GameField::fieldClicked, this, &MainWindow::handleFieldClick);
            QObject::connect(this, &MainWindow::callReset, field, &GameField::reset);
            QObject::connect(this, &MainWindow::updateFieldMark, field, &GameField::markUpdateCalled);
            field->setAlignment(Qt::AlignLeft);
            field->setGeometry(50 * column - 27, 50 * row - 21, 50, 50);
            field->show();
        }
    }
    updateBoardDisplay();
}

MainWindow::~MainWindow() {
    delete ui;
    delete game;
}

void MainWindow::highlightNeighbours(int origin_x, int origin_y) {
    emit updateFieldPiece(origin_x - 1, origin_y, PieceType::PAWN);
    emit updateFieldPiece(origin_x, origin_y - 1, PieceType::PAWN);
    emit updateFieldPiece(origin_x + 1, origin_y, PieceType::PAWN);
    emit updateFieldPiece(origin_x, origin_y + 1, PieceType::PAWN);
}


void MainWindow::on_newGameButton_clicked() {
    newGame(false);
}

/**
 * updates the state of fields in the window
 * to the state of the internal game
 *
 * TODO: change it so that it passes a color and piece type or the filename of the new icon instead of just piece Type
 */
void MainWindow::updateBoardDisplay() {
    for (int row = 1; row <= BOARD_SIZE; row++) {
        for (int col = 1; col <= BOARD_SIZE; col++) {
            auto piece = this->game->getPiece(Position(row, col));
            auto type = (piece != nullptr) ? piece->getType() : PieceType::NONE;
            emit updateFieldPiece(col, row, type);
        }
    }
}

/**
 * activated by emitting a "fieldClicked" signal by a connected @class GameField
 * handles everything related to picking a piece and making moves
 *
 * if there is no field selected, it will select that field
 * if a field is selected:
 *          - if the clicked field is one where a piece from the selected field can move, make that move
 *          - if not, select the newly clicked field and un-select the old one
 *
 * @param field
 */
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

/**
 * check whether a field is the endpoint of one of the moves that are currenly
 * being considered for the selected piece (if any)
 *
 *
 * @param moves
 * @param field
 * @return the move with an endpoint at the given field, or nullptr if such a move is not found
 */
Move *MainWindow::findMove(const std::vector<Move> &moves, const GameField *field) {
    Move *foundMove = nullptr;
    for (auto move: moves) {
        Position goal = move.getTo();
        if (goal.getCol() == field->getX() && goal.getRow() == field->getY()) {
            foundMove = &move;
            break;
        }
    }
    if (foundMove != nullptr) {
        return new Move(*foundMove);
    } else {
        return nullptr;
    }

}

void MainWindow::makeMove(Move const move) {
    game->makeMove(move);
    updateBoardDisplay();
    if (game->isMate()) {
        // what happens when mate?
    } else if (botGame) {
        //make bot move
    };
    updateBoardDisplay();
}


/**
 * Makes sure that the state of all fields is consistent after de-selecting a piece (ex. after a move)
 * or selecting a new one
 * @param new_picked - the field that is now supposed to be considered for moves etc.
 */
void MainWindow::changePickedField(GameField *const new_picked) {

    if (pickedField != nullptr) {
        // mark the previously picked field as not marked anymore
        emit updateFieldPiece(pickedField->getX(), pickedField->getY(), pickedField->getPiece());
        emit updateFieldMark(pickedField->getX(), pickedField->getY(),false);
        // TODO: create a function updating all marks/highlights here

    }
    if (new_picked != nullptr) { // if the new picked is a field
        validMoves = game->getMovesFrom(Position(new_picked->getY(), new_picked->getX()));
        // update the mark of the newly picked field
        emit updateFieldPiece(new_picked->getX(), new_picked->getY(), new_picked->getPiece());
        emit updateFieldMark(new_picked->getX(), new_picked->getY(), true);
        // TODO: create a function resetting all marks/highlights here
    } else {
        validMoves.clear();
    }
    emit callReset();

    pickedField = new_picked;
    if (pickedField != nullptr){
        emit updateFieldMark(pickedField->getX(), pickedField->getY(), true);
    }
    for (auto move: validMoves){
        int dest_x = move.getTo().getCol();
        int dest_y = move.getTo().getRow();
        emit updateFieldMark(dest_x, dest_y, true);
    }
}

void MainWindow::newGame(bool botGame, std::string whiteName, std::string blackName, Color botColor) {
    changePickedField(nullptr);
    emit callReset();
    delete game;
    game = new Game(whiteName, blackName);
    this->botGame = botGame;
    // if bot color == white, make first move
    updateBoardDisplay();


}

void MainWindow::on_actionstart_new_pvp_game_triggered() {
    newGame(false);
}

