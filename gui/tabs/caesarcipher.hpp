#pragma once

#include <QWidget>

namespace Ui {
    class CaesarCipher;
}

class CaesarCipher : public QWidget {
    Q_OBJECT

public:
    explicit CaesarCipher(QWidget *parent = nullptr);
    ~CaesarCipher();

private slots:
    void on_messageEdit_textChanged();

    void on_codeEdit_textChanged();

    void on_keySpin_valueChanged(int arg1);

    void on_addAlphabetButton_clicked();

private:
    Ui::CaesarCipher *ui;
    void encodeMessage();
    void decodeMessage();
};

