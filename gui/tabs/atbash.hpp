#ifndef ATBASHTAB_H
#define ATBASHTAB_H

#include <QWidget>

namespace Ui {
class Atbash;
}

class Atbash : public QWidget
{
    Q_OBJECT

public:
    explicit Atbash(QWidget* parent = nullptr);
    ~Atbash();

signals:
    void message(const QString& message, int timeout = 0);

private slots:
    void on_messageEdit_textChanged();
    void on_switchButton_clicked();

private:
    Ui::Atbash* ui;
};

#endif // ATBASHTAB_H
