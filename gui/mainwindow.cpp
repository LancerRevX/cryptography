#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "tabs/polybiussquare.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_polybiusSquareButton_clicked()
{
    auto window = new PolybiusSquare();
    window->show();
}
