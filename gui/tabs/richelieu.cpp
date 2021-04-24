#include "richelieu.hpp"
#include "ui_richelieu.h"

#include "ciphers.hpp"

#include <QDebug>

Richelieu::Richelieu(QWidget* parent) : QWidget(parent), ui(new Ui::Richelieu) {
    ui->setupUi(this);
}

Richelieu::~Richelieu() {
    delete ui;
}

void Richelieu::on_EncodeButton_clicked() {

}

std::vector<std::vector<size_t>> Richelieu::getKey() {
    auto text = ui->KeyEdit->text();
    return std::vector<std::vector<size_t>>();
}
