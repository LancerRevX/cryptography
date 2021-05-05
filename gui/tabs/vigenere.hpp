#ifndef VIGENERE_HPP
#define VIGENERE_HPP

#include <QWidget>

namespace Ui {
class Vigenere;
}

class Vigenere : public QWidget
{
    Q_OBJECT

public:
    explicit Vigenere(QWidget *parent = nullptr);
    ~Vigenere();

private slots:
    void on_AddAlphabetButton_clicked();

    void on_EncodeButton_clicked();

    void on_DecodeButton_clicked();

private:
    Ui::Vigenere *ui;
};

#endif // VIGENERE_HPP
