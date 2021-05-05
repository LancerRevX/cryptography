#ifndef HILL_HPP
#define HILL_HPP

#include <QWidget>

namespace Ui {
    class Hill;
}

class Hill : public QWidget
{
    Q_OBJECT

public:
    explicit Hill(QWidget *parent = nullptr);
    ~Hill();

private slots:
    void on_EncodeButton_clicked();

    void on_DecodeButton_clicked();

    void on_KeySizeSpin_valueChanged(int arg1);

private:
    Ui::Hill *ui;
};

#endif // HILL_HPP
