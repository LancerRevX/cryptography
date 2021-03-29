#include "caesarcipher.hpp"
#include "ui_caesarcipher.h"

#include "ciphers.hpp"

#include <QInputDialog>

CaesarCipher::CaesarCipher(QWidget *parent) : QWidget(parent), ui(new Ui::CaesarCipher) {
    ui->setupUi(this);
}

CaesarCipher::~CaesarCipher() {
    delete ui;
}

void CaesarCipher::encodeMessage() {
    std::vector<std::wstring> alphabets(ui->alphabetsList->count());
    for (int i = 0; i < ui->alphabetsList->count(); i++) {
        alphabets[i] = ui->alphabetsList->item(i)->text().toStdWString();
    }
    ui->codeEdit->blockSignals(true);
    ui->codeEdit->setPlainText(QString::fromStdWString(
        caesar_cipher::encode(
            ui->messageEdit->toPlainText().toStdWString(),
            ui->keySpin->value(),
            alphabets
        )
    ));
    ui->codeEdit->blockSignals(false);
}

void CaesarCipher::decodeMessage() {
    std::vector<std::wstring> alphabets(ui->alphabetsList->count());
    for (int i = 0; i < ui->alphabetsList->count(); i++) {
        alphabets[i] = ui->alphabetsList->item(i)->text().toStdWString();
    }
    ui->messageEdit->blockSignals(true);
    ui->messageEdit->setPlainText(QString::fromStdWString(
        caesar_cipher::decode(
            ui->codeEdit->toPlainText().toStdWString(),
            ui->keySpin->value(),
            alphabets
        )
    ));
    ui->messageEdit->blockSignals(false);
}

void CaesarCipher::on_messageEdit_textChanged() {
    this->encodeMessage();
}

void CaesarCipher::on_codeEdit_textChanged() {
    this->decodeMessage();
}

void CaesarCipher::on_keySpin_valueChanged(int)
{
    this->encodeMessage();
}

void CaesarCipher::on_addAlphabetButton_clicked() {
    QInputDialog dialog(this);
    if (dialog.exec()) {
        ui->alphabetsList->addItem(dialog.textValue());
    }
}
