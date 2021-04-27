#pragma once

#include <QWidget>

namespace Ui {
    class AlbertiDisk;
}

class AlbertiDisk : public QWidget
{
    Q_OBJECT

public:
    explicit AlbertiDisk(QWidget *parent = nullptr);
    ~AlbertiDisk();

private slots:
    void on_russianAlphabetButton_clicked();

    void on_englishAlphabetButton_clicked();

    void on_randomInnerDiskButton_clicked();

    void on_encodeButton_clicked();

    void on_decodeButton_clicked();

private:
    Ui::AlbertiDisk *ui;
};

