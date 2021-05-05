#ifndef GRONSVELD_HPP
#define GRONSVELD_HPP

#include <QWidget>

namespace Ui {
class Gronsveld;
}

class Gronsveld : public QWidget {
    Q_OBJECT

public:
    explicit Gronsveld(QWidget *parent = nullptr);
    ~Gronsveld();

private slots:
    void on_AddAlphabetButton_clicked();

    void on_KeyEdit_textChanged(const QString&);

    void on_MessageEdit_textChanged();

    void on_CodeEdit_textChanged();

private:
    Ui::Gronsveld *ui;

    void encode_message();
    void decode_code();
};

#endif // GRONSVELD_HPP
