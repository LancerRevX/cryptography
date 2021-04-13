#include "richelieu.hpp"
#include "ui_richelieu.h"

Richelieu::Richelieu(QWidget* parent) : QWidget(parent), ui(new Ui::Richelieu) {
    ui->setupUi(this);
}

Richelieu::~Richelieu() {
    delete ui;
}
