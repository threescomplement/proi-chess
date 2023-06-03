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
#include <QDialog>
#include <QInputDialog>
#include <QDir>
#include "ChessExceptions.h"
#include <QMessageBox>
#include "Player.h"

#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8

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
 **/
MainWindow::MainWindow(Game *game, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), game(game), pickedField(nullptr) {


    ui->setupUi(this);
    QPixmap board_map(":/resources/symmetrical_empty_board.jpg");
    ui->GameBoard->setPixmap(board_map);

    for (int row = 1; row <= BOARD_HEIGHT; row++) {
        for (int column = 1; column <= BOARD_WIDTH; column++) {
            auto *field = new GameField(QString(), column, 9 - row, ui->GameBoard);
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


void MainWindow::on_newGameButton_clicked() {
    newGame(false);
}

/**
 * updates the state of fields in the window
 * to the state of the internal game
 *
 * TODO: change it so that it passes a color and piece type or the filename of the new icon instead of just piece Type
 **/
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
 * Activated by emitting a "fieldClicked" signal by a connected @class GameField.
 * Handles everything related to picking a piece and making moves.
 *
 * If there is no field selected, it will select that field.
 * If a field is selected:
 *          - if the clicked field is one where a piece from the selected field can move, make that move,
 *          - if not, check if that field can be selected (must be a pawn of current player)
 *
 * @param field
 **/
void MainWindow::handleFieldClick(GameField *field) {

    if (field != pickedField) {
        bool validChoice = false;
        // check if there is a move to the chosen position
        Move *correspondingMove = findMove(validMoves, field);
        if (correspondingMove != nullptr) {
            makeMove(correspondingMove);
            changePickedField(nullptr);
            validChoice = true;
            // check if the field exists or if its just being reset
        } else if (field != nullptr) {
            // get piece from that field
            Piece *piece = game->getPiece(Position(field->getY(), field->getX()));
            if (piece != nullptr &&
                game->getCurrentPlayer() != nullptr) { // check if the piece and current player exist
                if (piece->getColor() == game->getCurrentPlayer()->getColor()) { // check if the piece belongs to player
                    changePickedField(field);
                    validChoice = true;
                }
            }

        }
        if (!validChoice){
            changePickedField(nullptr);
        }
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
 **/
Move *MainWindow::findMove(const std::vector<Move> &moves, const GameField *field) {
    for (auto move: moves) {
        Position goal = move.getTo();
        if (goal.getCol() == field->getX() && goal.getRow() == field->getY()) {
            return new Move(move);
        }
    }
    return nullptr;

}

void MainWindow::makeMove(Move const *move) {
    game->makeMove(*move);
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
 **/
void MainWindow::changePickedField(GameField *const new_picked) {

    if (pickedField != nullptr) {
        // mark the previously picked field as not marked anymore
        emit updateFieldPiece(pickedField->getX(), pickedField->getY(), pickedField->getPiece());
        emit updateFieldMark(pickedField->getX(), pickedField->getY(), false);

    }
    if (new_picked != nullptr) { // if the new picked is a field
        validMoves = game->getMovesFrom(Position(new_picked->getY(), new_picked->getX()));
        // update the mark of the newly picked field
        emit updateFieldPiece(new_picked->getX(), new_picked->getY(), new_picked->getPiece());
        emit updateFieldMark(new_picked->getX(), new_picked->getY(), true);
    } else {
        validMoves.clear();
    }
    emit callReset();

    pickedField = new_picked;
    if (pickedField != nullptr) {
        emit updateFieldMark(pickedField->getX(), pickedField->getY(), true);
    }
    for (auto move: validMoves) {
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

void MainWindow::on_actionRegular_game_triggered() {
    newGame(false);
}

void MainWindow::newFenGame(bool botGame, std::string fenNotation, std::string whiteName, std::string blackName,
                            Color bot_color) {
    //newGame(botGame, whiteName, blackName, bot_color);
    Game *new_game = nullptr;
    try {
        new_game = new Game(Game::fromFEN(fenNotation));
        game = new_game;
        // TODO: handle bot
        updateBoardDisplay();

    } catch (FenException) {
        // incorrect fen notation
        delete new_game;
        // display warning pop-up
        QMessageBox::warning(
                this,
                tr("Invalid FEN notation"),
                tr("Failed to initialise game from given FEN notation. \n"));

    }
    delete new_game;
}


void MainWindow::on_actionGame_from_FEN_triggered() {
    bool ok;

    QString text = QInputDialog::getText(this, tr("New Fen notation game"),
                                         tr("Enter the FEN notation:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);

    if (ok) {
        newFenGame(false, text.toStdString());
    }


}

