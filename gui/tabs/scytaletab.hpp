#pragma once

#include <QWidget>

namespace Ui {
    class ScytaleTab;
}

class ScytaleTab : public QWidget
{
    Q_OBJECT

public:
    explicit ScytaleTab(QWidget* parent = nullptr);
    ~ScytaleTab();

private slots:
    void on_messageEdit_textChanged();
    void on_codeEdit_textChanged();
    void on_rodFacesEdit_valueChanged(int rodFacesNumber);
    void on_rodCharLengthEdit_valueChanged(int arg1);
    void on_switchButton_clicked();

private:
    void encodeMessage();
    void decodeMessage();

    Ui::ScytaleTab *ui;
};

