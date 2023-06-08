#include <QPixmap>
#include <QDialog>
#include <QInputDialog>
#include <QDir>
#include <QThread>
#include <QMessageBox>
#include <QClipboard>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GameField.h"
#include "constants.h"
#include "Position.h"
#include "Move.h"
#include "ChessExceptions.h"
#include "Player.h"
#include "GameHandler.h"
#include "FENParser.h"






MainWindow::MainWindow(Game *game, QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow),
          pickedField(nullptr) {

    gameHandler = new GameHandler(game);
    ui->setupUi(this);
    ui->GameLayout->setGeometry(QRect(0, 0, 400, 400));
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    createBoard();

    updateBoardDisplay();
}


MainWindow::~MainWindow() {
    delete ui;
    delete gameHandler;
}


void MainWindow::createBoard(Color side) {
    QPixmap board_map = ((side == Color::WHITE)
                         ? QPixmap(":/resources/empty_board_white_perspective.png")
                         : QPixmap(":/resources/empty_board_black_perspective.png"));
    board_map = board_map.scaled(BOARD_SIDE_LENGTH, BOARD_SIDE_LENGTH, Qt::AspectRatioMode::KeepAspectRatio);
    if (ui->GameBoard->pixmap().toImage() != board_map.toImage()) {
        ui->GameBoard->setPixmap(board_map);
        ui->GameBoard->setAlignment(Qt::AlignLeft);
        ui->GameBoard->setGeometry(0, 0, BOARD_SIDE_LENGTH, BOARD_SIDE_LENGTH);


        for (auto child: ui->GameBoard->children()) {
            delete child;
        }
        for (int row = 1; row <= BOARD_ROWS; row++) {
            for (int column = 1; column <= BOARD_COLUMNS; column++) {
                int fieldRow;
                int fieldColumn;
                if (side == Color::WHITE) {
                    fieldRow = 9 - row;
                    fieldColumn = column;
                } else {
                    fieldRow = row;
                    fieldColumn = 9 - column;
                }
                int fieldSize = BOARD_SIDE_LENGTH / 8;
                auto *field = new GameField(QString(), fieldColumn, fieldRow, ui->GameBoard);
                QObject::connect(this, &MainWindow::updateFieldPiece, field, &GameField::updatePieceCalled);
                QObject::connect(field, &GameField::fieldClicked, this, &MainWindow::handleFieldClick);
                QObject::connect(this, &MainWindow::callReset, field, &GameField::reset);
                QObject::connect(this, &MainWindow::updateFieldMark, field, &GameField::markUpdateCalled);
                field->setAlignment(Qt::AlignLeft);
                field->setGeometry(fieldSize * (column - 1), fieldSize * (row - 1), fieldSize, fieldSize);
                field->show();
            }
        }
    }
}


void MainWindow::updateBoardDisplay() {
    for (int row = 1; row <= BOARD_SIZE; row++) {
        for (int col = 1; col <= BOARD_SIZE; col++) {
            auto piece = gameHandler->getPiece(Position(row, col));
            emit updateFieldPiece(col, row, piece);
        }
    }
    std::string currentPlayer = ((gameHandler->getCurrentPlayerColor() == Color::WHITE) ? "White" : "Black");
    currentPlayer += "'s turn";
    ui->statusbar->showMessage(QString::fromStdString(currentPlayer));
    for (const auto &move: gameHandler->getValidMoves()) {
        int dest_x = move.getTo().getCol();
        int dest_y = move.getTo().getRow();
        emit updateFieldMark(dest_x, dest_y, true);
    }
}


void MainWindow::handleFieldClick(GameField *field) {

    if (field == nullptr) {
        changePickedField(nullptr);
        return;
    }
    if (field != pickedField) {
        // check if there is a move to the chosen position
        Position fieldPos(field->getY(), field->getX());
        Move *correspondingMove = gameHandler->findMoveTo(fieldPos);
        if (correspondingMove != nullptr) {
            changePickedField(nullptr);
            makeMove(correspondingMove);
            // check if the field exists or if its just being reset
        } else if (gameHandler->fieldBelongsToCurrent(fieldPos)) {
            changePickedField(field);
        } else {
            changePickedField(nullptr);
        }
    }

}

void MainWindow::makeMove(Move *move) {

    if (move->resultsInPromotion()) {
        bool ok_button_pressed;
        QStringList colorPicker = {"Rook", "Knight", "Bishop", "Queen"};
        QString pickedPiece = QInputDialog::getItem(this, tr("Promotion"), tr("Choose piece to promote to:"),
                                                    colorPicker, 0,
                                                    false, &ok_button_pressed);
        std::map<QString, PieceType> pickToPieceMap = {{"Rook",   PieceType::ROOK},
                                                       {"Knight", PieceType::KNIGHT},
                                                       {"Bishop", PieceType::BISHOP},
                                                       {"Queen",  PieceType::QUEEN}};
        if (!ok_button_pressed) {
            return;
        }
        move->setPromotion(pickToPieceMap[pickedPiece]);
    }
    gameHandler->makeMove(move);
    updateBoardDisplay();
    if (!checkGameOver()) {
        //make bot move
        gameHandler->handleBotMove();
        updateBoardDisplay();
        checkGameOver();
    }
}


void MainWindow::changePickedField(GameField *const new_picked) {

    if (pickedField != nullptr) {
        // mark the previously picked field as not marked anymore
        emit updateFieldMark(pickedField->getX(), pickedField->getY(), false);

    }
    if (new_picked != nullptr) { // if the new picked is a field

        gameHandler->loadMovesFromPosition(Position(new_picked->getY(), new_picked->getX()));
        // update the mark of the newly picked field
        emit updateFieldMark(new_picked->getX(), new_picked->getY(), true);
    } else {
        gameHandler->clearMoves();
    }
    emit callReset();

    pickedField = new_picked;
    if (pickedField != nullptr) {
        emit updateFieldMark(pickedField->getX(), pickedField->getY(), true);
    }

    updateBoardDisplay();
}

void MainWindow::newGame(bool botGame, Color botColor, const std::string &fenNotation) {
    gameHandler->newGame(botGame, botColor, fenNotation);

    createBoard((botColor == Color::WHITE) ? Color::BLACK : Color::WHITE);
    changePickedField(nullptr);

    if (botGame) {

        int bot_depth = QInputDialog::getInt(this, tr("Bot difficulty"),
                                             tr("Enter the bot's search depth (the higher the depth,"
                                                " the more accurate the bot will be):"),
                                             QLineEdit::Normal,
                                             1);
        gameHandler->setBotDepth(bot_depth);
    }
    gameHandler->handleBotMove();
    updateBoardDisplay();
}


void MainWindow::newFenGame(bool isBotGame, Color bot_color) {
    bool ok_button_pressed;
    QString fenNotation = QInputDialog::getText(this, tr("New Fen notation game"),
                                                tr("Enter the FEN notation:"), QLineEdit::Normal,
                                                QDir::home().dirName(), &ok_button_pressed);
    if (!ok_button_pressed) {
        return;
    }
    try {
        newGame(isBotGame, bot_color, fenNotation.toStdString());
    } catch (FenException &e) {
        // incorrect fen notation
        // display warning pop-up
        QMessageBox::warning(
                this,
                tr("Invalid FEN notation"),
                tr("Failed to initialise game from given FEN notation. \n")
        );

    }

}

bool MainWindow::checkGameOver() {
    GameOver state = gameHandler->isTerminalState();
    std::string title = "Game Over";
    std::string userMessage;
    switch (state) {
        case GameOver::NOT_OVER: {
            return false;
        }
        case GameOver::MATE: {
            std::string winner = ((gameHandler->getCurrentPlayerColor() == Color::WHITE)
                                  ? "Black" : "White");
            winner += " is the winner!";
            userMessage = "Checkmate! " + winner;
            break;
        }
        case GameOver::STALEMATE: {
            userMessage = "Draw - Stalemate!";
            break;
        }
        case GameOver::INSUFFICIENT_MATERIAL: {
            userMessage = "Draw - Insufficient material for further play!";
            break;
        }
        case GameOver::FIFTY_MOVE_RULE: {
            userMessage = "Be so for real rn";
            break;
        }
        case GameOver::THREEFOLD_REPETITION: {
            userMessage = "Draw - Same position repeated 3 times!";
            break;
        }

    }
    QMessageBox::warning(
            this,
            QString::fromStdString(title),
            QString::fromStdString(userMessage));
    ui->statusbar->showMessage(QString::fromStdString(userMessage));

    return true;
}

void MainWindow::on_actionGame_from_FEN_triggered() {
    newFenGame(false);
}


void MainWindow::on_actionNew_classic_bot_game_triggered() {
    bool ok_button_pressed;
    QStringList colorPicker = {"White", "Black"};
    QString pickedColor = QInputDialog::getItem(this, tr("Choose your color"), tr("Choose your color:"), colorPicker, 0,
                                                false, &ok_button_pressed);

    if (ok_button_pressed) {
        newGame(true, (pickedColor == "White") ? Color::BLACK : Color::WHITE);
    }
}

void MainWindow::on_actionRegular_game_triggered() {
    newGame(false);
}


void MainWindow::on_actionNew_bot_game_from_FEN_triggered() {
    bool ok_button_pressed;
    QStringList colorPicker = {"White", "Black"};
    QString pickedColor = QInputDialog::getItem(this, tr("Choose your color"), tr("Choose your color:"), colorPicker, 0,
                                                false, &ok_button_pressed);

    if (ok_button_pressed) {
        newFenGame(true, (pickedColor == "White") ? Color::BLACK : Color::WHITE);
    }
}


void MainWindow::on_actionCopy_FEN_to_clipboard_triggered() {
    QClipboard *clipboard = QApplication::clipboard();
    QString text = QString::fromStdString(gameHandler->getGameFen());
    clipboard->setText(text, QClipboard::Clipboard);

    if (clipboard->supportsSelection()) {
        clipboard->setText(text, QClipboard::Selection);
    }

#if defined(Q_OS_LINUX)
    QThread::msleep(1); //workaround copying on linux not working properly
#endif
}


void MainWindow::on_actionUndo_move_triggered() {
    gameHandler->undo();
    updateBoardDisplay();
}


void MainWindow::on_actionRedo_move_triggered() {
    gameHandler->redo();
    updateBoardDisplay();
}



