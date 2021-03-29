#pragma once

#include <QWidget>

namespace Ui {
    class PolybiusSquare;
}

class PolybiusSquare : public QWidget
{
    Q_OBJECT

public:
    explicit PolybiusSquare(QWidget *parent = nullptr);
    ~PolybiusSquare();

private slots:
    void on_messageEdit_textChanged();

    void on_square_cellChanged(int row, int column);

    void on_codeEdit_textChanged();

    void on_methodSwitch_currentIndexChanged(int index);

    void on_squareSizeSpin_valueChanged(int size);

private:
    Ui::PolybiusSquare *ui;
    void encodeMessage();
    void decodeMessage();
    std::wstring (*encodingFunction)(
        std::wstring const&,
        std::vector<std::vector<std::wstring>> const&
    );
    std::wstring (*decodingFunction)(
        std::wstring const&,
        std::vector<std::vector<std::wstring>> const&
    );
};

