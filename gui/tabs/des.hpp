#pragma once

#include <QWidget>

namespace Ui {
    class DES;
}

class DES : public QWidget
{
    Q_OBJECT

public:
    explicit DES(QWidget *parent = nullptr);
    ~DES();

private:
    Ui::DES *ui;
};

