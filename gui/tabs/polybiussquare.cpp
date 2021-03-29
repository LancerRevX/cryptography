#include "polybiussquare.hpp"
#include "ui_polybiussquare.h"

#include "ciphers.hpp"

#include <QDebug>

PolybiusSquare::PolybiusSquare(QWidget* parent) : QWidget(parent), ui(new Ui::PolybiusSquare) {
    ui->setupUi(this);
    this->encodingFunction = &polybius_square::method_1::encode;
    this->decodingFunction = &polybius_square::method_1::decode;
}

PolybiusSquare::~PolybiusSquare() {
    delete ui;
}

void PolybiusSquare::on_messageEdit_textChanged() {
    this->encodeMessage();
}

void PolybiusSquare::encodeMessage() {
    auto message {ui->messageEdit->toPlainText()};
    std::vector<std::vector<std::wstring>> square(ui->square->rowCount());
    for (auto i = 0; i < ui->square->rowCount(); i++) {
        square[i].resize(ui->square->columnCount());
        for (auto j = 0; j < ui->square->columnCount(); j++) {
            square[i][j] = ui->square->item(i, j) ?
                ui->square->item(i, j)->text().toStdWString() :
                L"";
        }
    }
    ui->codeEdit->blockSignals(true);
    ui->codeEdit->setPlainText(QString::fromStdWString(
        this->encodingFunction(message.toStdWString(), square)
    ));
    ui->codeEdit->blockSignals(false);
}

void PolybiusSquare::decodeMessage() {
    auto code {ui->codeEdit->toPlainText()};
    std::vector<std::vector<std::wstring>> square(ui->square->rowCount());
    for (auto i = 0; i < ui->square->rowCount(); i++) {
        square[i].resize(ui->square->columnCount());
        for (auto j = 0; j < ui->square->columnCount(); j++) {
            square[i][j] = ui->square->item(i, j) ?
                ui->square->item(i, j)->text().toStdWString() :
                L"";
        }
    }
    ui->messageEdit->blockSignals(true);
    ui->messageEdit->setPlainText(QString::fromStdWString(
        this->decodingFunction(code.toStdWString(), square)
    ));
    ui->messageEdit->blockSignals(false);
}

void PolybiusSquare::on_square_cellChanged(int, int) {
    this->encodeMessage();
}

void PolybiusSquare::on_codeEdit_textChanged() {
    this->decodeMessage();
}

void PolybiusSquare::on_methodSwitch_currentIndexChanged(int index) {
    switch (index) {
        case 0:
            this->encodingFunction = &polybius_square::method_1::encode;
            this->decodingFunction = &polybius_square::method_1::decode;
            break;
        case 1:
            this->encodingFunction = &polybius_square::method_2::encode;
            this->decodingFunction = &polybius_square::method_2::decode;
            break;
        case 2:
            this->encodingFunction = &polybius_square::method_3::encode;
            this->decodingFunction = &polybius_square::method_3::decode;
            break;
    }
    this->encodeMessage();
}

void PolybiusSquare::on_squareSizeSpin_valueChanged(int size) {
    ui->square->setRowCount(size);
    ui->square->setColumnCount(size);
    this->encodeMessage();
}
