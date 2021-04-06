#include "cardangrille.hpp"
#include "ui_cardangrille.h"

#include "ciphers.hpp"
#include <qdebug.h>
#include <QMessageBox>

CardanGrille::CardanGrille(QWidget *parent) : QWidget(parent), ui(new Ui::CardanGrille) {
    ui->setupUi(this);
    this->updateGrille();
    //ui->grille->setStyleSheet("QTableWidget::item:selected{ background-color: none; }");
    ui->grille->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->grille->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->codeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->codeTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

CardanGrille::~CardanGrille() {
    delete ui;
}

void CardanGrille::on_grille_clicked(const QModelIndex &index) {
    auto cell = ui->grille->item(index.row(), index.column());
    cell->setBackground(cell->background() == Qt::green ? Qt::red : Qt::green);
}

void CardanGrille::updateGrille() {
    for (int i = 0; i < ui->grille->rowCount(); i++) {
        for (int j = 0; j < ui->grille->columnCount(); j++) {
            if (!ui->grille->item(i, j)) {
                ui->grille->setItem(i, j, new QTableWidgetItem);
                ui->grille->item(i, j)->setBackground(Qt::green);
            }
        }
    }
}

void CardanGrille::on_grilleSizeSpin_valueChanged(int size) {
    ui->grille->setRowCount(size);
    ui->grille->setColumnCount(size);
    this->updateGrille();
}

void CardanGrille::on_encodeButton_clicked() {
    try {
        cardan_grille::encode(L"", std::vector<std::vector<bool>>(), true);
    }  catch (cardan_grille::GrilleAndCodeDoNotMatch&) {
        QMessageBox::warning(this, "Ошибка",
            "Размеры зашифрованного сообщения и решётки не совпадают."
        );
    }
}
