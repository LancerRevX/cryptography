#pragma once

#include <QWidget>

namespace Ui {
    class CardanGrille;
}

class CardanGrille : public QWidget {
    Q_OBJECT

public:
    explicit CardanGrille(QWidget *parent = nullptr);
    ~CardanGrille();

private slots:
    void on_grille_clicked(const QModelIndex &index);

    void on_grilleSizeSpin_valueChanged(int arg1);

    void on_encodeButton_clicked();


    void on_decodeButton_clicked();

    void on_codeTableSizeSpin_valueChanged(int arg1);

    void on_grilleRotateButton_clicked();

private:
    Ui::CardanGrille *ui;
    void updateGrille();
    void updateCodeTable();
};

