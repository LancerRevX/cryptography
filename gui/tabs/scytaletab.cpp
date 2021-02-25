#include "scytaletab.hpp"
#include "ui_scytaletab.h"

#include <ciphers.hpp>

#include <QDebug>
#include <QMessageBox>

ScytaleTab::ScytaleTab(QWidget* parent) : QWidget(parent), ui(new Ui::ScytaleTab) {
    ui->setupUi(this);
    auto rodFacesNumber = ui->rodFacesEdit->value();
    auto rodCharLength = ui->rodCharLengthEdit->value();
    ui->codeTable->setColumnCount(rodCharLength);
    ui->codeTable->setRowCount(rodFacesNumber);
}

ScytaleTab::~ScytaleTab() {
    delete ui;
}

void ScytaleTab::on_messageEdit_textChanged() {
    this->encodeMessage();
}

void ScytaleTab::on_codeEdit_textChanged() {
    this->decodeMessage();
}

void ScytaleTab::on_rodFacesEdit_valueChanged(int rodFacesNumber) {
    ui->codeTable->setRowCount(rodFacesNumber);

    this->encodeMessage();
}

void ScytaleTab::on_rodCharLengthEdit_valueChanged(int rodCharLength) {
    ui->codeTable->setColumnCount(rodCharLength);

    this->encodeMessage();
}

void ScytaleTab::on_switchButton_clicked() {
    ui->messageEdit->setPlainText(ui->codeEdit->toPlainText());
    this->encodeMessage();
}

void ScytaleTab::encodeMessage()
{
    auto message = ui->messageEdit->toPlainText();
    if (message.length() > (ui->rodFacesEdit->value() * ui->rodCharLengthEdit->value())) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Сообщение не может быть длиннее произведения длины палочки в символах на количество её граней."
        ).exec();
        ui->messageEdit->setPlainText(message.chopped(message.length() - ui->rodFacesEdit->value() * ui->rodCharLengthEdit->value()));
        return;
    }
    auto rodFacesNumber = ui->rodFacesEdit->value();
    auto rodCharLength = ui->rodCharLengthEdit->value();
    auto code = QString::fromStdWString(scytale::encode(
        message.toStdWString(),
        rodFacesNumber,
        rodCharLength
    ));
    qDebug() << message;
    qDebug() << code;
    ui->codeEdit->blockSignals(true);
    ui->codeEdit->setPlainText(code);
    ui->codeEdit->blockSignals(false);
    for (int i = 0; i < rodFacesNumber; i += 1) {
        for (int j = 0; j < rodCharLength; j += 1) {
            ui->codeTable->setItem(
                i, j, new QTableWidgetItem(QString(code[i + j*rodFacesNumber]))
            );
        }
    }
}

void ScytaleTab::decodeMessage() {
    auto code = ui->codeEdit->toPlainText();
    auto rodFacesNumber = ui->rodFacesEdit->value();
    auto rodCharLength = ui->rodCharLengthEdit->value();
    auto message = QString::fromStdWString(scytale::decode(
        code.toStdWString(),
        rodFacesNumber,
        rodCharLength
    ));
    if (code.length() != rodFacesNumber * rodCharLength) {
        ui->messageEdit->blockSignals(true);
        ui->messageEdit->setPlainText("");
        ui->messageEdit->blockSignals(false);
        return;
    }

    ui->messageEdit->blockSignals(true);
    ui->messageEdit->setPlainText(message);
    ui->messageEdit->blockSignals(false);
    for (int i = 0; i < rodFacesNumber; i += 1) {
        for (int j = 0; j < rodCharLength; j += 1) {
            ui->codeTable->setItem(
                i, j, new QTableWidgetItem(QString(message[j + i*rodCharLength]))
            );
        }
    }
}

