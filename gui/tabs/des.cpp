#include "des.hpp"
#include "ui_des.h"

#include <QRegularExpressionValidator>

DES::DES(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DES)
{
    ui->setupUi(this);
    ui->keyEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[01]{0,56}")));
}

DES::~DES()
{
    delete ui;
}
