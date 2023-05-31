#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "clickable_label.h"
#include "GameField.h"
#include "../chess/Game.h"

MainWindow::MainWindow(Game *game, QWidget *parent)
        : MainWindow(parent) {
    this->game = game;
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
            GameField *field = new GameField(QString("Nie kliknięte"), column, row, this);
            QObject::connect(this, &MainWindow::update_field, field, &GameField::update_called);
            QObject::connect(field, &GameField::fieldClicked, this, &MainWindow::highlightNeighbours);
            field->setAlignment(Qt::AlignLeft);
            field->setGeometry(50 * column - 20, 50 * row + 20, 50, 50);
            field->show();
            if (row == 1) { // black
                switch (column) {
                    case 1:
                    case 8:
                        emit update_field(column, row, 9); // rook
                        break;
                    case 2:
                    case 7:
                        emit update_field(column, row, 11); // knight
                        break;
                    case 3:
                    case 6:
                        emit update_field(column, row, 10); // bishop
                        break;
                    case 4:
                        emit update_field(column, row, 8);  // queen 💅
                        break;
                    case 5:
                        emit update_field(column, row, 7); // king 👑
                        break;
                }

            } else if (row == 2) { // black
                emit update_field(column, row, 12); // pawn
            }
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
    emit update_field(origin_x - 1, origin_y, (origin_y + origin_x) % 13);
    emit update_field(origin_x, origin_y - 1, (origin_y + origin_x) % 13);
    emit update_field(origin_x + 1, origin_y, (origin_y + origin_x) % 13);
    emit update_field(origin_x, origin_y + 1, (origin_y + origin_x) % 13);

}


// create a


void MainWindow::on_newGameButton_clicked() {

}

