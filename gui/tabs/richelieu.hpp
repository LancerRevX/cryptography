#pragma once

#include <QWidget>

namespace Ui {
class Richelieu;
}

class Richelieu : public QWidget {
    Q_OBJECT

public:
    explicit Richelieu(QWidget *parent = nullptr);
    ~Richelieu();

private:
    Ui::Richelieu *ui;
};
