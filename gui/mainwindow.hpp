#pragma once

#include <QMainWindow>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_polybiusSquareButton_clicked();
    void on_atbashButton_clicked();

    void on_scytaleButton_clicked();

    void on_caesarButton_clicked();

    void on_pushButton_clicked();

    void on_richelieuButton_clicked();

private:
    Ui::MainWindow* ui;
};
