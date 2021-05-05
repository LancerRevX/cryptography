#include "hill.hpp"
#include "ui_hill.h"

#include "ciphers.hpp"

#include <QMessageBox>

Hill::Hill(QWidget *parent) : QWidget(parent), ui(new Ui::Hill) {
    ui->setupUi(this);
}

Hill::~Hill() {
    delete ui;
}

void Hill::on_EncodeButton_clicked() {
    try {
        std::vector<std::vector<int>> key(ui->KeyTable->rowCount());
        for (int i {0}; i < ui->KeyTable->rowCount(); i++) {
            key[i].resize(ui->KeyTable->columnCount());
            for (int j {0}; j < ui->KeyTable->columnCount(); j++) {
                key[i][j] = ui->KeyTable->item(i, j)->text().toInt();
            }
        }
        ui->CodeEdit->setPlainText(QString::fromStdWString(
            hill::encode(ui->MessageEdit->toPlainText().toStdWString(), ui->AlphabetEdit->text().toStdWString(), key)
        ));
    } catch (hill::InvalidKey&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
                    "Размер ключа должен соответствовать длине сообщения."
                    ).exec();
    } catch (hill::InvalidAlphabet&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
                    "В алфавите не должно быть повторяющихся символов."
                    ).exec();
    } catch (hill::InvalidMessage&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
                    "Сообщение должно состоять из символов выбранного алфавита."
                    ).exec();
    } catch (hill::KeyIsNotInvertible&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
                    "Матрица ключа должна быть обратима."
                    ).exec();
    }
}

void Hill::on_DecodeButton_clicked() {
    try {
        std::vector<std::vector<int>> key(ui->KeyTable->rowCount());
        for (int i {0}; i < ui->KeyTable->rowCount(); i++) {
            key[i].resize(ui->KeyTable->columnCount());
            for (int j {0}; j < ui->KeyTable->columnCount(); j++) {
                key[i][j] = ui->KeyTable->item(i, j)->text().toInt();
            }
        }
        ui->MessageEdit->setPlainText(QString::fromStdWString(
            hill::decode(ui->CodeEdit->toPlainText().toStdWString(), ui->AlphabetEdit->text().toStdWString(), key)
            ));
    } catch (hill::InvalidKey&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
                    "Размер ключа должен соответствовать длине криптограммы."
                    ).exec();
    } catch (hill::InvalidAlphabet&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
                    "В алфавите не должно быть повторяющихся символов."
                    ).exec();
    } catch (hill::InvalidMessage&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
                    "Криптограмма должна состоять из символов выбранного алфавита."
                    ).exec();
    } catch (hill::KeyIsNotInvertible&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
                    "Матрица ключа должна быть обратима."
                    ).exec();
    }
}

void Hill::on_KeySizeSpin_valueChanged(int size) {
    ui->KeyTable->setRowCount(size);
    ui->KeyTable->setColumnCount(size);
    for (int i {0}; i < ui->KeyTable->rowCount(); i++) {
        for (int j {0}; j < ui->KeyTable->columnCount(); j++) {
            if (not ui->KeyTable->item(i, j)) {
                ui->KeyTable->setItem(i, j, new QTableWidgetItem("0"));
            }
        }
    }
}
