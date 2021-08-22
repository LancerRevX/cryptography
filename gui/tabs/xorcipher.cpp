#include "xorcipher.hpp"
#include "ui_xorcipher.h"

#include <QMessageBox>

#include "ciphers.hpp"

XorCipher::XorCipher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XorCipher)
{
    ui->setupUi(this);
}

XorCipher::~XorCipher()
{
    delete ui;
}

void XorCipher::on_generateKeyButton_clicked()
{
    ui->keyEdit->setPlainText(
        QString::fromStdWString(xor_cipher::generate_key(
            ui->messageEdit->toPlainText().length(),
            ui->seedEdit->text().toStdWString()[0],
            ui->multiplierSpin->value(),
            ui->incrementSpin->value()
        ))
    );
}

void XorCipher::on_encodeButton_clicked()
{
    try {
        ui->codeEdit->setPlainText(
            QString::fromStdWString(xor_cipher::encode(
                ui->messageEdit->toPlainText().toStdWString(),
                ui->keyEdit->toPlainText().toStdWString()
            ))
        );
    } catch (xor_cipher::KeyDoesNotMatchMessage& error) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Гамма-последовательность не должна быть короче исходного сообщения"
        ).exec();
    }
}

void XorCipher::on_decodeButton_clicked()
{
    try {
        ui->messageEdit->setPlainText(
            QString::fromStdWString(xor_cipher::decode(
                ui->codeEdit->toPlainText().toStdWString(),
                ui->keyEdit->toPlainText().toStdWString()
            ))
        );
    } catch (xor_cipher::KeyDoesNotMatchMessage& error) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Гамма-последовательность не должна быть короче шифртекста"
        ).exec();
    }
}
