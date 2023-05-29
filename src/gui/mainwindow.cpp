#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "clickable_label.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QPixmap board_map(":/resources/Empty_Board.jpg");
    ui->GameBoard->setPixmap(board_map);
    ClickableLabel *click_label = new ClickableLabel(QString("poczatkowy tekst"), this);
    //ui->GameLayout->addWidget(click_label);
    click_label->setAlignment(Qt::AlignRight);
    click_label->setGeometry(50, 100, 50, 50);
    click_label->show();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::move(int start_x, int start_y) {

}

void MainWindow::on_pushButton_69_clicked()
{

}

