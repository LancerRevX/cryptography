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

    void on_albertiDiskButton_clicked();

    void on_GronsveldButton_clicked();

    void on_VigenereButton_clicked();

    void on_PlayfairButton_clicked();

    void on_HillButton_clicked();

    void on_VernamButton_clicked();

    void on_FrequencyAnalysisButton_clicked();

    void on_xorCipherButton_clicked();

private:
    Ui::MainWindow* ui;
};
