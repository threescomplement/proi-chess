
#include <QPixmap>
#include <vector>
#include <QDialog>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>
#include <QClipboard>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GameField.h"
#include "constants.h"
#include "Position.h"
#include "Move.h"
#include "pieces/Piece.h"
#include "pieces/PieceType.h"
#include "ChessExceptions.h"
#include "Player.h"
#include "../bot/StockfishBot.h"

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
        : QMainWindow(parent), ui(new Ui::MainWindow), game(game), pickedField(nullptr), botGame(false), stockfishBot(
        nullptr), botColor(Color::BLACK) {

    this->resize(400, 400);
    ui->setupUi(this);
    //ui->GameLayout->setSizeConstraint(QLayout::SetFixedSize);
//    this->setMaximumSize(400, 450);
//    this->setMinimumSize(400, 450);
    ui->GameLayout->setGeometry(QRect(0, 0, 400, 400));
    setFixedSize(400, 445);
    createBoard();

    updateBoardDisplay();
}


MainWindow::~MainWindow() {
    delete ui;
    delete game;
}


void MainWindow::createBoard(Color side) {
    QPixmap board_map = ((side == Color::WHITE) ? QPixmap(":/resources/empty_board_white_perspective.png") : QPixmap(
            ":/resources/empty_board_black_perspective.png"));
    board_map = board_map.scaled(400, 400, Qt::AspectRatioMode::KeepAspectRatio);
    if (ui->GameBoard->pixmap().toImage() != board_map.toImage()) {
        ui->GameBoard->setPixmap(board_map);
        ui->GameBoard->setAlignment(Qt::AlignLeft);
        ui->GameBoard->setGeometry(0, 0, 400, 400);


        for (auto child: ui->GameBoard->children()) {
            delete child;
        }
        for (int row = 1; row <= BOARD_HEIGHT; row++) {
            for (int column = 1; column <= BOARD_WIDTH; column++) {
                int fieldRow;
                int fieldColumn;
                if (side == Color::WHITE) {
                    fieldRow = 9 - row;
                    fieldColumn = column;
                } else {
                    fieldRow = row;
                    fieldColumn = 9 - column;
                }
                auto *field = new GameField(QString(), fieldColumn, fieldRow, ui->GameBoard);
                QObject::connect(this, &MainWindow::updateFieldPiece, field, &GameField::updatePieceCalled);
                QObject::connect(field, &GameField::fieldClicked, this, &MainWindow::handleFieldClick);
                QObject::connect(this, &MainWindow::callReset, field, &GameField::reset);
                QObject::connect(this, &MainWindow::updateFieldMark, field, &GameField::markUpdateCalled);
                field->setAlignment(Qt::AlignLeft);
                field->setGeometry(50 * (column - 1), 50 * (row - 1), 50, 50);
                field->show();
            }
        }
    }


}


/**
 * updates the state of fields in the window
 * to the state of the internal game
 *
 *
 **/
void MainWindow::updateBoardDisplay() {
    for (int row = 1; row <= BOARD_SIZE; row++) {
        for (int col = 1; col <= BOARD_SIZE; col++) {
            auto piece = this->game->getPiece(Position(row, col));
            auto type = (piece != nullptr) ? piece->getType() : PieceType::NONE;
            auto color = (piece != nullptr) ? piece->getColor() : Color::WHITE;
            emit updateFieldPiece(col, row, type, color);
        }
    }
    std::string currentPlayer = ((game->getCurrentPlayer()->getColor() == Color::WHITE) ? "White" : "Black");
    currentPlayer += "'s turn";
    ui->statusbar->showMessage(QString::fromStdString(currentPlayer));
    if (game->isMate()) {
        ui->statusbar->showMessage("Checkmate!");
    } else if (game->isCheck(game->getCurrentPlayer()->getColor())) {
        ui->statusbar->showMessage("Check!");
    } else if (game->isStalemate()) {
        ui->statusbar->showMessage("Stalemate!");
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

    // TODO - Could be cleaned up a bit
    if (field != pickedField) {
        bool validChoice = false;
        // check if there is a move to the chosen position
        Move *correspondingMove = findMove(validMoves, field);
        if (correspondingMove != nullptr) {
            changePickedField(nullptr);
            makeMove(correspondingMove);

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
        if (!validChoice) {
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
    //not implemented in game logic yet :
//    if (game.promotionFlag){
//        bool ok;
//        PieceType pickedType = PieceType::NONE;
//        QStringList colorPicker = {"Rook", "Knight", "Bishop", "Queen"};
//        QString pickedPiece = QInputDialog::getItem(this, tr("Promotion"), tr("Choose piece to promote to:"), colorPicker, 0,
//                                                    false, &ok);
//        if (ok){
//            switch (pickedPiece) {
//                case "Rook":
//                    pickedType = PieceType::ROOK;
//                    break;
//                case "Knight":
//                    pickedType = PieceType::KNIGHT;
//                    break;
//                case "Bishop":
//                    pickedType = PieceType::BISHOP;
//                    break;
//                case "Queen":
//                    pickedType = PieceType::QUEEN;
//                    break;
//            }
//        }
//        game.promote(pickedType);
//    }

    updateBoardDisplay();
    if (!(checkIfMate() || checkIfStalemate())) {
        //make bot move
        handleBotMove();
        updateBoardDisplay();
        checkIfMate();
        checkIfStalemate();

    }


}


/**
 * Makes sure that the state of all fields is consistent after de-selecting a piece (ex. after a move)
 * or selecting a new one
 * @param new_picked - the field that is now supposed to be considered for moves etc.
 **/
void MainWindow::changePickedField(GameField *const new_picked) {

    if (pickedField != nullptr) {
        // mark the previously picked field as not marked anymore
        emit updateFieldMark(pickedField->getX(), pickedField->getY(), false);

    }
    if (new_picked != nullptr) { // if the new picked is a field
        validMoves = game->getLegalMovesFrom(Position(new_picked->getY(), new_picked->getX()));
        // update the mark of the newly picked field
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

void MainWindow::newGame(bool botGame, Color botColor, std::string fenNotation) {
    Game *newGame = nullptr;
    try {
        newGame = new Game(Game::fromFEN(fenNotation));
    } catch (FenException e) {
        delete newGame;
        throw FenException("Incorrect Fen");
    }


    createBoard((botColor == Color::WHITE) ? Color::BLACK : Color::WHITE);

    changePickedField(nullptr);


    delete stockfishBot;


    delete game;
    game = newGame;
    this->botGame = botGame;
    this->botColor = botColor;
    if (this->botGame) {
        stockfishBot = new StockfishBot(*game);

        int bot_depth = QInputDialog::getInt(this, tr("Bot difficulty"),
                                             tr("Enter the bot's search depth (the higher the depth,"
                                                " the more accurate the bot will be):"),
                                             QLineEdit::Normal,
                                             0);
        // stockFishBot.setDepth(bot_depth);
    }
    handleBotMove();


    updateBoardDisplay();
}


void MainWindow::newFenGame(bool botGame, Color bot_color) {

    bool ok;

    QString fenNotation = QInputDialog::getText(this, tr("New Fen notation game"),
                                                tr("Enter the FEN notation:"), QLineEdit::Normal,
                                                QDir::home().dirName(), &ok);
    if (ok) {
        try {
            newGame(botGame, bot_color, fenNotation.toStdString());
        } catch (FenException) {
            // incorrect fen notation
            // display warning pop-up
            QMessageBox::warning(
                    this,
                    tr("Invalid FEN notation"),
                    tr("Failed to initialise game from given FEN notation. \n"));

        }
    }

}


void MainWindow::on_actionGame_from_FEN_triggered() {


    newFenGame(false);

}


void MainWindow::on_actionNew_classic_bot_game_triggered() {
    bool ok;
    QStringList colorPicker = {"White", "Black"};
    QString pickedColor = QInputDialog::getItem(this, tr("Choose your color"), tr("Choose your color:"), colorPicker, 0,
                                                false, &ok);

    if (ok) {
        newGame(true, (pickedColor == "White") ? Color::BLACK : Color::WHITE);
    }
}

void MainWindow::on_actionRegular_game_triggered() {
    newGame(false);
}


void MainWindow::on_actionNew_bot_game_from_FEN_triggered() {
    bool ok;
    QStringList colorPicker = {"White", "Black"};
    QString pickedColor = QInputDialog::getItem(this, tr("Choose your color"), tr("Choose your color:"), colorPicker, 0,
                                                false, &ok);

    if (ok) {
        newFenGame(true, (pickedColor == "White") ? Color::BLACK : Color::WHITE);
    }


}


void MainWindow::handleBotMove() {
    if (botGame && botColor == game->getCurrentPlayer()->getColor()) {

        Move botMove = stockfishBot->getBestNextMove();
        game->makeMove(botMove);


    }
}

bool MainWindow::checkIfMate() {
    if (game->isMate()) {
        std::string winner = ((game->getCurrentPlayer()->getColor() == Color::WHITE) ? "Black" : "White");
        winner += "is the winner!";
        QMessageBox::warning(
                this,
                tr("Game Over"),
                QString::fromStdString(winner));

    }
    ui->statusbar->showMessage("Checkmate!");
    return game->isMate();
}


void MainWindow::on_actionCopy_FEN_to_clipboard_triggered() {
    QClipboard *clipboard = QApplication::clipboard();
    QString text = QString::fromStdString(game->toFEN());
    clipboard->setText(text, QClipboard::Clipboard);

    if (clipboard->supportsSelection()) {
        clipboard->setText(text, QClipboard::Selection);
    }

#if defined(Q_OS_LINUX)
    QThread::msleep(1); //workaround copying on linux not working properly
#endif
}

bool MainWindow::checkIfStalemate() {
    if (game->isStalemate()) {
        QMessageBox::warning(
                this,
                tr("Game Over"),
                tr("Stalemate!"));
    }
    ui->statusbar->showMessage("Stalemate!");
    return game->isStalemate();
}

