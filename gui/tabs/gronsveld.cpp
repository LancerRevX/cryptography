#include "gronsveld.hpp"
#include "ui_gronsveld.h"

#include <QRegularExpressionValidator>
#include <QInputDialog>

#include "ciphers.hpp"

Gronsveld::Gronsveld(QWidget* parent) : QWidget(parent), ui(new Ui::Gronsveld) {
    ui->setupUi(this);
    ui->KeyEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("\\d*"), this));
}

Gronsveld::~Gronsveld() {
    delete ui;
}

void Gronsveld::encode_message() {
    std::vector<std::wstring> alphabets(ui->AlphabetsList->count());
    for (int i {0}; i < ui->AlphabetsList->count(); i++) {
        alphabets[i] = ui->AlphabetsList->item(i)->text().toStdWString();
    }

    std::vector<size_t> key(ui->KeyEdit->text().length());
    for (int i {0}; i < ui->KeyEdit->text().length(); i++) {
        key[i] = QString(ui->KeyEdit->text().at(i)).toLongLong();
    }

    ui->CodeEdit->blockSignals(true);
    ui->CodeEdit->setPlainText(QString::fromStdWString(
        gronsveld::encode(ui->MessageEdit->toPlainText().toStdWString(), alphabets, key)
    ));
    ui->CodeEdit->blockSignals(false);
}

void Gronsveld::decode_code() {
    std::vector<std::wstring> alphabets(ui->AlphabetsList->count());
    for (int i {0}; i < ui->AlphabetsList->count(); i++) {
        alphabets[i] = ui->AlphabetsList->item(i)->text().toStdWString();
    }

    std::vector<size_t> key(ui->KeyEdit->text().length());
    for (int i {0}; i < ui->KeyEdit->text().length(); i++) {
        key[i] = QString(ui->KeyEdit->text().at(i)).toLongLong();
    }

    ui->MessageEdit->blockSignals(true);
    ui->MessageEdit->setPlainText(QString::fromStdWString(
        gronsveld::decode(ui->CodeEdit->toPlainText().toStdWString(), alphabets, key)
    ));
    ui->MessageEdit->blockSignals(false);
}

void Gronsveld::on_AddAlphabetButton_clicked() {
    QInputDialog dialog(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint);
    dialog.setLabelText("Введите новый алфавит:");
    dialog.setWindowTitle("Новый алфавит");
    if (dialog.exec()) {
        ui->AlphabetsList->addItem(dialog.textValue());
        this->encode_message();
    }
}

void Gronsveld::on_KeyEdit_textChanged(const QString&) {
    this->encode_message();
}

void Gronsveld::on_MessageEdit_textChanged() {
    this->encode_message();
}

void Gronsveld::on_CodeEdit_textChanged() {
    this->decode_code();
}
