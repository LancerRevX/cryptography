#include "vernam.hpp"
#include "ui_vernam.h"

#include "ciphers.hpp"

Vernam::Vernam(QWidget *parent) :
      QWidget(parent),
      ui(new Ui::Vernam)
{
    ui->setupUi(this);
}

Vernam::~Vernam()
{
    delete ui;
}

void Vernam::encode_message() {
    ui->CodeEdit->blockSignals(true);
    ui->CodeEdit->setPlainText(QString::fromStdWString(
        vernam::encode(
            ui->MessageEdit->toPlainText().toStdWString(),
            ui->KeyEdit->toPlainText().toStdWString()
        )
    ));
    ui->CodeEdit->blockSignals(false);
}

void Vernam::decode_code() {
    ui->MessageEdit->blockSignals(true);
    ui->MessageEdit->setPlainText(QString::fromStdWString(
        vernam::encode(
            ui->CodeEdit->toPlainText().toStdWString(),
            ui->KeyEdit->toPlainText().toStdWString()
        )
    ));
    ui->MessageEdit->blockSignals(false);
}

void Vernam::on_KeyEdit_textChanged() {
    this->encode_message();
}

void Vernam::on_MessageEdit_textChanged() {
    this->encode_message();
}

void Vernam::on_CodeEdit_textChanged() {
    this->decode_code();
}
