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

private slots:
    void on_EncodeButton_clicked();

    void on_DecodeButton_clicked();

private:
    Ui::Richelieu *ui;
    std::vector<std::vector<size_t>> getKey();
};
