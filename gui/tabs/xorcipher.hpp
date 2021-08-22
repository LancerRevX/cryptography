#pragma once

#include <QWidget>

namespace Ui {
    class XorCipher;
}

class XorCipher : public QWidget
{
    Q_OBJECT

public:
    explicit XorCipher(QWidget *parent = nullptr);
    ~XorCipher();

private slots:
    void on_generateKeyButton_clicked();

    void on_encodeButton_clicked();

    void on_decodeButton_clicked();

private:
    Ui::XorCipher *ui;
};

