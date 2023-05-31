#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./ClickableLabel.h"
#include "Game.h"
#include "pieces/PieceType.h"
#include <vector>
#include "Move.h"
#include "GameField.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

private:
    Game *game;
    GameField *pickedField; // currently selected field
    std::vector<Move> validMoves; // moves possible from that field



    void updateBoardDisplay();

    Move *findMove(const std::vector<Move> &moves, const GameField *field);

    void changePickedField(GameField *const new_picked);

public:
    MainWindow(Game *game = new Game("player1", "player2"), QWidget *parent = nullptr);

    MainWindow(QWidget *parent);

    ~MainWindow();

    void makeMove(Move const move);


    //keep the positions or pointers to labels where a move starts and finishes
    // when a user clicks on an unmarked label, all other labels must be unmarked
    // and the new label is set as the "origin" of the move

    // create a vector of clickable labels that represent
    // all the fields. Each one might have a descriptor of position.
    // Connect signals from the labels to mainwindow, so that whenever
    // the user clicks on a button, it sends a signal with its position
    //  to the window and the window is updated
    // and proper methods are called on a Game object.
    // new moves have to be acquired every time an unmarked label is clicked.
    // After the main window receives proper information about moves,
    // it can update all the coresponding labels to "marked" or something..
    // then if a marked label is pressed and it's not the "starting" label, it emits a signal with its position
    // to make the move to this location.


    // maybe an "update board" function that gets a board and updates all images on it?
    // or change them during the make_move method?
public slots:


    void highlightNeighbours(int origin_x, int origin_y);

    void handleFieldClick(GameField *field);

signals:

    void update_field(int x, int y, PieceType type = PieceType::NONE, bool mark = false);

private slots:


    void on_newGameButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
