#pragma once

#include <QWidget>

namespace Ui {
    class Scytale;
}

class Scytale : public QWidget
{
    Q_OBJECT

public:
    explicit Scytale(QWidget* parent = nullptr);
    ~Scytale();

private slots:
    void on_messageEdit_textChanged();
    void on_codeEdit_textChanged();
    void on_rodFacesEdit_valueChanged(int rodFacesNumber);
    void on_rodCharLengthEdit_valueChanged(int arg1);
    void on_switchButton_clicked();

private:
    void encodeMessage();
    void decodeMessage();

    Ui::Scytale *ui;
};

