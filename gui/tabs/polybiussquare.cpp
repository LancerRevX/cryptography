#include "polybiussquare.hpp"
#include "ui_polybiussquare.h"

PolybiusSquare::PolybiusSquare(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PolybiusSquare)
{
    ui->setupUi(this);
}

PolybiusSquare::~PolybiusSquare()
{
    delete ui;
}
