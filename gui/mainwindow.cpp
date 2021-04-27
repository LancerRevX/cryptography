#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "tabs/atbash.hpp"
#include "tabs/scytale.hpp"
#include "tabs/polybiussquare.hpp"
#include "tabs/caesarcipher.hpp"
#include "tabs/cardangrille.hpp"
#include "tabs/richelieu.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);
//    this->on_polybiusSquareButton_clicked();
}

MainWindow::~MainWindow() {
    delete this->ui;
}

void MainWindow::on_atbashButton_clicked() {
    auto window = new Atbash();
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::on_scytaleButton_clicked() {
    auto window = new Scytale();
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::on_polybiusSquareButton_clicked() {
    auto window = new PolybiusSquare();
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::on_caesarButton_clicked() {
    auto window = new CaesarCipher();
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::on_pushButton_clicked() {
    auto window = new CardanGrille();
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::on_richelieuButton_clicked() {
    auto window = new Richelieu();
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
}
