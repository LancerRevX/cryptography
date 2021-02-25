#include "atbashtab.hpp"
#include "ui_atbashtab.h"

#include <ciphers.hpp>

#include <QRegExpValidator>
#include <QMessageBox>
#include <QDebug>

AtbashTab::AtbashTab(QWidget* parent) : QWidget(parent), ui(new Ui::AtbashTab) {
    ui->setupUi(this);
//    ui->messageEdit->setValidator(new QRegExpValidator(QRegExp("^[а-яёА-ЯЁa-zA-Z .,!?]+$")));
}

AtbashTab::~AtbashTab() {
    delete ui;
}

void AtbashTab::on_messageEdit_textChanged() {
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

void AtbashTab::on_switchButton_clicked() {
    ui->messageEdit->setText(ui->codeEdit->toPlainText());
}
