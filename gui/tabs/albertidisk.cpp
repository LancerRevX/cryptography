#include "albertidisk.hpp"
#include "ui_albertidisk.h"

#include <QMessageBox>

#include "ciphers.hpp"

AlbertiDisk::AlbertiDisk(QWidget* parent) : QWidget(parent), ui(new Ui::AlbertiDisk) {
    ui->setupUi(this);
}

AlbertiDisk::~AlbertiDisk() {
    delete ui;
}

void AlbertiDisk::on_russianAlphabetButton_clicked() {
    ui->outerDiskEdit->setText("абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ");
}

void AlbertiDisk::on_englishAlphabetButton_clicked() {
    ui->outerDiskEdit->setText("abcdefghijklmnoprstuvwxyzABCDEFGHIJKLMNOPRSTUVWXYZ");
}

void AlbertiDisk::on_randomInnerDiskButton_clicked() {
    auto alphabet = ui->outerDiskEdit->text();
    std::random_shuffle(alphabet.begin(), alphabet.end());
    ui->innerDiskEdit->setText(alphabet);
}

void AlbertiDisk::on_encodeButton_clicked() {
    try {
        ui->codeEdit->setPlainText(
            QString::fromStdWString(alberti_disk::encode(
                ui->messageEdit->toPlainText().toStdWString(),
                ui->outerDiskEdit->text().toStdWString(),
                ui->innerDiskEdit->text().toStdWString(),
                ui->spinStepSpin->value()
            ))
        );
    } catch (alberti_disk::DisksDontMatch&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Диски должны быть одного размера"
        ).exec();
    }
}

void AlbertiDisk::on_decodeButton_clicked() {
    try {
        ui->messageEdit->setPlainText(
            QString::fromStdWString(alberti_disk::decode(
                ui->codeEdit->toPlainText().toStdWString(),
                ui->outerDiskEdit->text().toStdWString(),
                ui->innerDiskEdit->text().toStdWString(),
                ui->spinStepSpin->value()
            ))
        );
    } catch (alberti_disk::DisksDontMatch&) {
        QMessageBox(QMessageBox::Warning, "Ошибка",
            "Диски должны быть одного размера"
        ).exec();
    }
}
