#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./ClickableLabel.h"
#include "Game.h"
#include "pieces/PieceType.h"
#include <vector>
#include "Move.h"
#include "GameField.h"
#include "Color.h"


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
    Game *game;
    GameField *pickedField; // currently selected field
    std::vector<Move> validMoves; // moves possible from that field
    bool botGame;


    void updateBoardDisplay();

    Move *findMove(const std::vector<Move> &moves, const GameField *field);

    void changePickedField(GameField *const new_picked);


public:
    MainWindow(Game *game = new Game("player1", "player2"), QWidget *parent = nullptr);

    ~MainWindow();

    void makeMove(Move const *move);

    void newGame(bool botGame, std::string whiteName = "Player 1", std::string blackName = "Player 2",
                 Color bot_color = Color::BLACK);
    void newFenGame(bool botGame, std::string fenNotation ,std::string whiteName = "Player 1", std::string blackName = "Player 2",
                    Color bot_color = Color::BLACK);


public slots:



    void handleFieldClick(GameField *field);


signals:

    void updateFieldPiece(int x, int y, PieceType type = PieceType::NONE);

    void updateFieldMark(int x, int y, bool newMark);


    void callReset();

private slots:


    void on_newGameButton_clicked();

    void on_actionRegular_game_triggered();

    void on_actionGame_from_FEN_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
