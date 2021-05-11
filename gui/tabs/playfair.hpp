#ifndef PLAYFAIR_HPP
#define PLAYFAIR_HPP

#include <QWidget>

namespace Ui {
    class Playfair;
}

class Playfair : public QWidget
{
    Q_OBJECT

public:
    explicit Playfair(QWidget *parent = nullptr);
    ~Playfair();

private slots:
    void on_EnglishAlphabetButton_clicked();

    void on_RussianAlphabetButton_clicked();

    void on_AlphabetHeightSpin_valueChanged(int arg1);

    void on_AlphabetWidthSpin_valueChanged(int arg1);

    void on_EncodeButton_clicked();

    void on_DecodeButton_clicked();

    void on_RussianAlphabet8x4Button_clicked();

private:
    Ui::Playfair *ui;
};

#endif // PLAYFAIR_HPP
