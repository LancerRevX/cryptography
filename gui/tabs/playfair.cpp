#include "playfair.hpp"
#include "ui_playfair.h"

#include "ciphers.hpp"

#include <QMessageBox>

Playfair::Playfair(QWidget* parent) : QWidget(parent), ui(new Ui::Playfair) {
    ui->setupUi(this);
}

Playfair::~Playfair() {
    delete ui;
}

void Playfair::on_EnglishAlphabetButton_clicked() {
    static QVector<QVector<QString>> const english_alphabet {
        {"A", "B", "C", "D", "E"},
        {"F", "G", "H", "IJ", "K"},
        {"L", "M", "N", "O", "P"},
        {"Q", "R", "S", "T", "U"},
        {"V", "W", "X", "Y", "Z"}
    };
    ui->AlphabetHeightSpin->setValue(english_alphabet.size());
    ui->AlphabetWidthSpin->setValue(english_alphabet[0].size());
    for (int i {0}; i < english_alphabet.size(); i++) {
        for (int j {0}; j < english_alphabet[i].size(); j++) {
            ui->AlphabetTable->setItem(i, j, new QTableWidgetItem(english_alphabet[i][j]));
        }
    }
    ui->StubEdit->setText("X");
}

void Playfair::on_RussianAlphabetButton_clicked() {
    static QVector<QVector<QString>> const russian_alphabet {
        {"А", "Б", "В", "Г", "Д", "ЕЁ", "Ж", "З"},
        {"И", "Й", "К", "Л", "М", "Н", "О", "П"},
        {"Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч"},
        {"Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я"}
    };
    ui->AlphabetHeightSpin->setValue(russian_alphabet.size());
    ui->AlphabetWidthSpin->setValue(russian_alphabet[0].size());
    for (int i {0}; i < russian_alphabet.size(); i++) {
        for (int j {0}; j < russian_alphabet[i].size(); j++) {
            ui->AlphabetTable->setItem(i, j, new QTableWidgetItem(russian_alphabet[i][j]));
        }
    }
    ui->StubEdit->setText("Ы");
}

void Playfair::on_AlphabetHeightSpin_valueChanged(int height) {
    ui->AlphabetTable->setRowCount(height);
    for (int i {0}; i < ui->AlphabetTable->rowCount(); i++) {
        for (int j {0}; j < ui->AlphabetTable->columnCount(); j++) {
            if (not ui->AlphabetTable->item(i, j)) {
                ui->AlphabetTable->setItem(i, j, new QTableWidgetItem(""));
            }
        }
    }
}

void Playfair::on_AlphabetWidthSpin_valueChanged(int width) {
    ui->AlphabetTable->setColumnCount(width);
    for (int i {0}; i < ui->AlphabetTable->rowCount(); i++) {
        for (int j {0}; j < ui->AlphabetTable->columnCount(); j++) {
            if (not ui->AlphabetTable->item(i, j)) {
                ui->AlphabetTable->setItem(i, j, new QTableWidgetItem(""));
            }
        }
    }
}

void Playfair::on_EncodeButton_clicked() {
    try {
        std::vector<std::vector<std::wstring>> alphabet(ui->AlphabetTable->rowCount());
        for (int i {0}; i < ui->AlphabetTable->rowCount(); i++) {
            alphabet[i].resize(ui->AlphabetTable->columnCount());
            for (int j {0}; j < ui->AlphabetTable->columnCount(); j++) {
                alphabet[i][j] = ui->AlphabetTable->item(i, j)->text().toStdWString();
            }
        }

        auto encoding_matrix {playfair::get_encoding_matrix(alphabet, ui->KeyEdit->text().toStdWString())};
        ui->EncodingMatrixTable->setRowCount(encoding_matrix.size());
        ui->EncodingMatrixTable->setColumnCount(encoding_matrix[0].size());
        for (size_t i {0}; i < encoding_matrix.size(); i++) {
            for (size_t j {0}; j < encoding_matrix[i].size(); j++) {
                ui->EncodingMatrixTable->setItem(i, j, new QTableWidgetItem(QString::fromStdWString(encoding_matrix[i][j])));
            }
        }

        auto digrams {playfair::get_digrams(ui->MessageEdit->toPlainText().toStdWString(), ui->StubEdit->text().toStdWString()[0])};
        QString digrams_string;
        for (auto& digram : digrams) {
            digrams_string += QString::fromStdWString(std::wstring(1, digram.first));
            digrams_string += QString::fromStdWString(std::wstring(1, digram.second));
            digrams_string += " ";
        }
        ui->DigramsEdit->setText(digrams_string);

        ui->CodeEdit->setPlainText(QString::fromStdWString(
            playfair::encode(
                ui->MessageEdit->toPlainText().toStdWString(),
                alphabet,
                ui->KeyEdit->text().toStdWString(),
                ui->StubEdit->text().toStdWString()[0]
            )
        ));
    } catch (playfair::InvalidAlphabet&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Неправильный алфавит."
        ).exec();
    } catch (playfair::InvalidMessage&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Неправильное сообщение."
        ).exec();
    } catch (playfair::InvalidKey&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Неправильное ключевое слово."
        ).exec();
    } catch (playfair::InvalidStub&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Неправильная заглушка."
        ).exec();
    }
}

void Playfair::on_DecodeButton_clicked() {
    try {
        std::vector<std::vector<std::wstring>> alphabet(ui->AlphabetTable->rowCount());
        for (int i {0}; i < ui->AlphabetTable->rowCount(); i++) {
            alphabet[i].resize(ui->AlphabetTable->columnCount());
            for (int j {0}; j < ui->AlphabetTable->columnCount(); j++) {
                alphabet[i][j] = ui->AlphabetTable->item(i, j)->text().toStdWString();
            }
        }

        auto encoding_matrix {playfair::get_encoding_matrix(alphabet, ui->KeyEdit->text().toStdWString())};
        ui->EncodingMatrixTable->setRowCount(encoding_matrix.size());
        ui->EncodingMatrixTable->setColumnCount(encoding_matrix[0].size());
        for (size_t i {0}; i < encoding_matrix.size(); i++) {
            for (size_t j {0}; j < encoding_matrix[i].size(); j++) {
                ui->EncodingMatrixTable->setItem(i, j, new QTableWidgetItem(QString::fromStdWString(encoding_matrix[i][j])));
            }
        }

        auto digrams {playfair::get_digrams(ui->CodeEdit->toPlainText().toStdWString(), ui->StubEdit->text().toStdWString()[0])};
        QString digrams_string;
        for (auto& digram : digrams) {
            digrams_string += QString::fromStdWString(std::wstring(1, digram.first));
            digrams_string += QString::fromStdWString(std::wstring(1, digram.second));
            digrams_string += " ";
        }
        ui->DigramsEdit->setText(digrams_string);

        ui->MessageEdit->setPlainText(QString::fromStdWString(
            playfair::decode(
                ui->CodeEdit->toPlainText().toStdWString(),
                alphabet,
                ui->KeyEdit->text().toStdWString(),
                ui->StubEdit->text().toStdWString()[0]
            )
        ));
    } catch (playfair::InvalidAlphabet&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Неправильный алфавит."
        ).exec();
    } catch (playfair::InvalidMessage&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Неправильное сообщение."
        ).exec();
    } catch (playfair::InvalidKey&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Неправильное ключевое слово."
        ).exec();
    } catch (playfair::InvalidStub&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Неправильная заглушка."
        ).exec();
    }
}

void Playfair::on_RussianAlphabet8x4Button_clicked()
{
    static QVector<QVector<QString>> const russian_alphabet {
        {"А", "Б", "В", "Г"},
        {"Д", "ЕЁ", "Ж", "З"},
        {"И", "Й", "К", "Л"},
        {"М", "Н", "О", "П"},
        {"Р", "С", "Т", "У"},
        {"Ф", "Х", "Ц", "Ч"},
        {"Ш", "Щ", "Ъ", "Ы"},
        {"Ь", "Э", "Ю", "Я"}
    };
    ui->AlphabetHeightSpin->setValue(russian_alphabet.size());
    ui->AlphabetWidthSpin->setValue(russian_alphabet[0].size());
    for (int i {0}; i < russian_alphabet.size(); i++) {
        for (int j {0}; j < russian_alphabet[i].size(); j++) {
            ui->AlphabetTable->setItem(i, j, new QTableWidgetItem(russian_alphabet[i][j]));
        }
    }
    ui->StubEdit->setText("Ы");
}
