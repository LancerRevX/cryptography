#include "cardangrille.hpp"
#include "ui_cardangrille.h"

#include "ciphers.hpp"
#include <qdebug.h>
#include <QMessageBox>

CardanGrille::CardanGrille(QWidget *parent) : QWidget(parent), ui(new Ui::CardanGrille) {
    ui->setupUi(this);
    this->updateGrille();
    //ui->grille->setStyleSheet("QTableWidget::item:selected{ background-color: none; }");
//    ui->grille->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->grille->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->codeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    ui->codeTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->updateCodeTable();
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

void CardanGrille::updateCodeTable() {
    for (int i = 0; i < ui->codeTable->rowCount(); i++) {
        for (int j = 0; j < ui->codeTable->columnCount(); j++) {
            if (!ui->codeTable->item(i, j)) {
                ui->codeTable->setItem(i, j, new QTableWidgetItem);
                ui->codeTable->item(i, j)->setText(0);
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
        std::vector<std::vector<bool>> grille(ui->grille->rowCount());
        for (int i = 0; i < ui->grille->rowCount(); i++) {
            grille[i].resize(ui->grille->columnCount());
            for (int j = 0; j < ui->grille->rowCount(); j++) {
                grille[i][j] = ui->grille->item(i, j)->background() == Qt::red;
            }
        }
        auto code = cardan_grille::encode(
            ui->messageEdit->toPlainText().toStdWString(),
            grille,
            ui->junkSwitch->currentIndex()
        );
        ui->codeTable->setRowCount(code.size());
        ui->codeTable->setColumnCount(code[0].size());
        this->updateCodeTable();
        ui->codeTableSizeSpin->setValue(code.size());
        for (size_t i = 0; i < code.size(); i++) {
            for (size_t j = 0; j < code[i].size(); j++) {
                ui->codeTable->item(i, j)->setText(QString::fromStdWString(wstring(1, code[i][j])));
            }
        }
    } catch (cardan_grille::MessageLongerThanHolesNumber&) {
        QMessageBox::warning(this, "Ошибка",
            "Сообщение не может быть длиннее количества дырок в решётке, умноженного на 4."
        );
    } catch (cardan_grille::MessageLengthNotEqualToHolesNumber&) {
        QMessageBox::warning(this, "Ошибка",
            "При шифровании без \"мусора\" длина сообщения должна быть равна количеству дырок в решётке, умноженному на 4."
        );
    } catch (cardan_grille::GrilleOverlaps&) {
        QMessageBox::warning(this, "Ошибка",
            "Дырки не должны пересекаться при повороте решётки."
        );
    }
}

void CardanGrille::on_decodeButton_clicked()
{
    try {
        vector<vector<wchar_t>> code(ui->codeTable->rowCount());
        for (int i = 0; i < ui->codeTable->rowCount(); i++) {
            code[i].resize(ui->codeTable->rowCount());
            for (int j = 0; j < ui->codeTable->columnCount(); j++) {
                code[i][j] = ui->codeTable->item(i, j)->text().toStdWString()[0];
            }
        }
        std::vector<std::vector<bool>> grille(ui->grille->rowCount());
        for (int i = 0; i < ui->grille->rowCount(); i++) {
            grille[i].resize(ui->grille->columnCount());
            for (int j = 0; j < ui->grille->rowCount(); j++) {
                grille[i][j] = ui->grille->item(i, j)->background() == Qt::red;
            }
        }
        ui->messageEdit->setPlainText(QString::fromStdWString(cardan_grille::decode(code, grille)));
    } catch (cardan_grille::GrilleAndCodeDoNotMatch&) {
        QMessageBox::warning(this, "Ошибка",
            "Размеры зашифрованного сообщения и решётки не совпадают."
        );
    }
}

void CardanGrille::on_codeTableSizeSpin_valueChanged(int size) {
    ui->codeTable->setRowCount(size);
    ui->codeTable->setColumnCount(size);
    this->updateCodeTable();
}

void CardanGrille::on_grilleRotateButton_clicked() {
    int n = ui->grille->rowCount();
    for (int i = 0; i < n / 2; i++) {
        for (int j = i; j < n - i - 1; j++) {
            auto tmp = ui->grille->item(i, j)->background();
            ui->grille->item(i, j)->setBackground(ui->grille->item(n - 1 - j, i)->background());
            ui->grille->item(n - 1 - j, i)->setBackground(ui->grille->item(n - 1 - i, n - 1 - j)->background());
            ui->grille->item(n - 1 - i, n - 1 - j)->setBackground(ui->grille->item(j, n - 1 - i)->background());
            ui->grille->item(j, n - 1 - i)->setBackground(tmp);
        }
    }

}
