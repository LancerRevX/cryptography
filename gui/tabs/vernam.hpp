#ifndef VERNAM_HPP
#define VERNAM_HPP

#include <QWidget>

namespace Ui {
    class Vernam;
}

class Vernam : public QWidget
{
    Q_OBJECT

public:
    explicit Vernam(QWidget *parent = nullptr);
    ~Vernam();

private slots:
    void on_KeyEdit_textChanged();

    void on_MessageEdit_textChanged();

    void on_CodeEdit_textChanged();

private:
    Ui::Vernam *ui;

    void encode_message();
    void decode_code();
};

#endif // VERNAM_HPP
