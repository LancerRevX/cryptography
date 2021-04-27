#include "richelieu.hpp"
#include "ui_richelieu.h"

#include "ciphers.hpp"

#include <QDebug>
#include <QRegularExpression>
#include <QMessageBox>

Richelieu::Richelieu(QWidget* parent) : QWidget(parent), ui(new Ui::Richelieu) {
    ui->setupUi(this);
}

Richelieu::~Richelieu() {
    delete ui;
}

void Richelieu::on_EncodeButton_clicked() {
    qDebug() << this->getKey();
    auto key = this->getKey();
    if (key.size() == 0) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Некорректный ключ"
        ).exec();
        return;
    }

    try {
        auto code = richelieu::encode(ui->MessageEdit->toPlainText().toStdWString(), key);
        ui->CodeEdit->setPlainText(QString::fromStdWString(code));
    } catch (richelieu::KeyLongerThanMessage&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Ключ длиннее сообщения"
        ).exec();
    } catch (richelieu::InvalidKeySegment&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Некорректный сегмент ключа"
        ).exec();
    }
}

void Richelieu::on_DecodeButton_clicked() {
    auto key = this->getKey();
    if (key.size() == 0) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Некорректный ключ"
        ).exec();
        return;
    }

    try {
        auto message = richelieu::decode(ui->CodeEdit->toPlainText().toStdWString(), key);
        ui->MessageEdit->setPlainText(QString::fromStdWString(message));
    } catch (richelieu::KeyLongerThanMessage&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Ключ длиннее сообщения"
        ).exec();
    } catch (richelieu::InvalidKeySegment&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Некорректный сегмент ключа"
        ).exec();
    }
}

std::vector<std::vector<size_t>> Richelieu::getKey() {
    std::vector<std::vector<size_t>> result;
    QRegularExpression regExp(R"(^({(?:\d+)\s*(?:,\s*\d+)*})(?:,\s*({(?:\d+)\s*(?:,\s*\d+)*}))*$)");
    if (not regExp.match(ui->KeyEdit->text()).hasMatch()) {
        return result;
    }

    QRegularExpression segmentRegExp(R"(({(?:\d+)\s*(?:,\s*\d+)*}))");
    auto segmentIterator = segmentRegExp.globalMatch(ui->KeyEdit->text());
    while (segmentIterator.hasNext()) {
        auto segment = segmentIterator.next().captured(0);
        QRegularExpression valueRegExp(R"(\d+)");
        result.resize(result.size() + 1);
        auto& result_segment {result[result.size() - 1]};
        auto valueIterator = valueRegExp.globalMatch(segment);
        while (valueIterator.hasNext()) {
            auto value = valueIterator.next().captured(0);
            result_segment.push_back(value.toULongLong());
        }
    }
    return result;
}
