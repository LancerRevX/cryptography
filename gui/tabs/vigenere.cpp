#include "vigenere.hpp"
#include "ui_vigenere.h"

#include <QInputDialog>
#include <QMessageBox>

#include "ciphers.hpp"

Vigenere::Vigenere(QWidget *parent) : QWidget(parent), ui(new Ui::Vigenere) {
    ui->setupUi(this);
}

Vigenere::~Vigenere() {
    delete ui;
}

void Vigenere::on_AddAlphabetButton_clicked() {
    QInputDialog dialog(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    dialog.setLabelText("Введите новый алфавит:");
    dialog.setWindowTitle("Новый алфавит");
    if (dialog.exec()) {
        ui->AlphabetsList->addItem(dialog.textValue());
    }
}

void Vigenere::on_EncodeButton_clicked() {
    try {
        ui->CodeEdit->setPlainText(QString::fromStdWString(
            vigenere::encode(
                ui->MessageEdit->toPlainText().toStdWString(),
                ui->AlphabetsList->currentItem()->text().toStdWString(),
                ui->KeyEdit->text().toStdWString()
            )
        ));
    } catch (vigenere::InvalidKey&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Ключ не может быть пустым и должен состоять из символов выбранного алфавита."
        ).exec();
    }
}

void Vigenere::on_DecodeButton_clicked()
{
    try {
        ui->MessageEdit->setPlainText(QString::fromStdWString(
            vigenere::decode(
                ui->CodeEdit->toPlainText().toStdWString(),
                ui->AlphabetsList->currentItem()->text().toStdWString(),
                ui->KeyEdit->text().toStdWString()
            )
        ));
    } catch (vigenere::InvalidKey&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Ключ не может быть пустым и должен состоять из символов выбранного алфавита."
        ).exec();
    }
}
