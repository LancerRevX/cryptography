#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "tabs/atbash.hpp"
#include "tabs/scytale.hpp"
#include "tabs/polybiussquare.hpp"
#include "tabs/caesarcipher.hpp"
#include "tabs/cardangrille.hpp"
#include "tabs/richelieu.hpp"
#include "tabs/albertidisk.hpp"
#include "tabs/gronsveld.hpp"
#include "tabs/vigenere.hpp"
#include "tabs/playfair.hpp"
#include "tabs/hill.hpp"
#include "tabs/vernam.hpp"

#include "tabs/frequency_analysis/frequency_analysis.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->ui->setupUi(this);
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

void MainWindow::on_albertiDiskButton_clicked() {
    auto window = new AlbertiDisk();
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::on_GronsveldButton_clicked() {
    auto window = new Gronsveld();
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::on_VigenereButton_clicked() {
    auto window = new Vigenere();
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
}


void MainWindow::on_PlayfairButton_clicked() {
    auto window = new Playfair();
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::on_HillButton_clicked() {
    auto window = new Hill();
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::on_VernamButton_clicked() {
    auto window = new Vernam();
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::on_FrequencyAnalysisButton_clicked()
{
    auto window = new FrequencyAnalysis();
    window->show();
    window->setAttribute(Qt::WA_DeleteOnClose);
}
