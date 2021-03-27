#include "atbash.hpp"
#include "ui_atbash.h"

#include <ciphers.hpp>

#include <QRegExpValidator>
#include <QMessageBox>
#include <QDebug>

Atbash::Atbash(QWidget* parent) : QWidget(parent), ui(new Ui::Atbash) {
    ui->setupUi(this);
//    ui->messageEdit->setValidator(new QRegExpValidator(QRegExp("^[а-яёА-ЯЁa-zA-Z .,!?]+$")));
}

Atbash::~Atbash() {
    delete ui;
}

void Atbash::on_messageEdit_textChanged() {
    auto message = ui->messageEdit->toPlainText();
    if (message.isEmpty()) {
        ui->codeEdit->setText("");
    } else if (!QRegExp("^[а-яёА-ЯЁa-zA-Z .,!?\n]+$").exactMatch(message)) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Сообщение может содержать только русские и латинские буквы, "
            "пробелы, точки, запятые, восклицательные и вопросительные знаки."
        ).exec();
        ui->messageEdit->setText(QString(message).remove(QRegExp("[^а-яёА-ЯЁa-zA-Z .,!?]+")));
    } else {
        ui->codeEdit->setText(QString::fromStdWString(atbash::encode(message.toStdWString())));
    }

}

void Atbash::on_switchButton_clicked() {
    ui->messageEdit->setText(ui->codeEdit->toPlainText());
}
