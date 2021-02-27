#pragma once

#include <QWidget>

namespace Ui {
    class PolybiusSquare;
}

class PolybiusSquare : public QWidget
{
    Q_OBJECT

public:
    explicit PolybiusSquare(QWidget *parent = nullptr);
    ~PolybiusSquare();

private:
    Ui::PolybiusSquare *ui;
};

