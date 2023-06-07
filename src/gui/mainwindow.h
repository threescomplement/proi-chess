#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "ClickableLabel.h"
#include "Game.h"
#include "pieces/PieceType.h"
#include "Move.h"
#include "GameField.h"
#include "Color.h"
#include "../bot/StockfishBot.h"
#include "Color.h"
#include "GameHandler.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/**
 * @class MainWindow
 * Qt window which handles the creation of almost the entire program.
 * Connects to @class GameField fields on the board via:
 * updateFieldPiece() (outgoing),
 * handleFieldClick() (incoming).
 *
 * handles keeping the state of the window and the internal game the same
 * and enables interaction with it
 *
 * TODO: Implement buttons/menu options allowing the user to start a new game with a bot
 *
 * Keeps a pointer to the currently selected field (piece).
 * When a user clicks on an unmarked field, the choice is reset
 * and the new field is set as the "origin" of the move, if it has a piece belonging to the current player.
 * Connects signals from the GameFields to mainwindow, so that whenever
 * the user clicks on a field, it sends a signal with a pointer to itself
 * to the window and the window is updated
 * and proper methods are called on the Game object.
 * New moves have to be acquired every time a piece of the current player is selected.
 * After the main window receives proper information about moves,
 * it can update all the corresponding labels to "marked", which in turn update their overlays.
 * Then if a marked label is pressed and it's not the "starting" label, different scenarios are handled
 * (selecting a different piece, un-selecting a piece entirely, resetting the choice by external factors).
 *
 *
 */
class MainWindow : public QMainWindow {
Q_OBJECT

private:
    GameField *pickedField; // currently selected field
    GameHandler *gameHandler;


    /**
     * updates the state of fields in the window
     * to the state of the internal game
     **/
    void updateBoardDisplay();

    /**
     * Makes sure that the state of all fields is consistent after de-selecting a piece (ex. after a move)
     * or selecting a new one
     * @param new_picked - the field that is now supposed to be considered for moves etc.
     **/
    void changePickedField(GameField *const new_picked);

    /**
    * displays the image of a board,
    * then sets up a 8 x 8 grid of GameField
    * to act as clickable tiles on the board.
    * Connects the appropriate signals between the fields and the window
    **/
    void createBoard(Color side = Color::WHITE);

    bool checkIfMate();

    bool checkIfStalemate();

public:

    /**
     * @param game - the game that will be played and displayed in the window
     * @param parent
     **/
    MainWindow(Game *game = new Game("player1", "player2"), QWidget *parent = nullptr);

    ~MainWindow();

    void makeMove(Move *move);

    void newGame(bool botGame, Color bot_color = Color::BLACK,
                 const std::string &fenNotation = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    void newFenGame(bool isBotGame, Color bot_color = Color::BLACK);


public slots:

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
    void handleFieldClick(GameField *field);


signals:

    void updateFieldPiece(int x, int y, Piece *piece = nullptr);

    void updateFieldMark(int x, int y, bool newMark);

    void callReset();

private slots:


    void on_actionRegular_game_triggered();

    void on_actionGame_from_FEN_triggered();

    void on_actionNew_classic_bot_game_triggered();

    void on_actionNew_bot_game_from_FEN_triggered();

    void on_actionCopy_FEN_to_clipboard_triggered();

    void on_actionUndo_move_triggered();

    void on_actionRedo_move_triggered();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
