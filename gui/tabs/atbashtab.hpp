#ifndef ATBASHTAB_H
#define ATBASHTAB_H

#include <QWidget>

namespace Ui {
class AtbashTab;
}

class AtbashTab : public QWidget
{
    Q_OBJECT

public:
    explicit AtbashTab(QWidget* parent = nullptr);
    ~AtbashTab();

signals:
    void message(const QString& message, int timeout = 0);

private slots:
    void on_messageEdit_textChanged();
    void on_switchButton_clicked();

private:
    Ui::AtbashTab* ui;
};

#endif // ATBASHTAB_H
