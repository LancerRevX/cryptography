#include "frequency_analysis.hpp"
#include "ui_frequency_analysis.h"

#include <QFileDialog>

#include <QDebug>

FrequencyAnalysis::FrequencyAnalysis(QWidget* parent) : QWidget(parent), ui(new Ui::FrequencyAnalysis)
{
    ui->setupUi(this);
    symbols_model.setParent(this);

    ui->TextFrequenciesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    auto average_frequencies_model {new AverageFrequenciesTableModel};
    average_frequencies_model->setSourceModel(&symbols_model);
    ui->AverageFrequenciesTable->setModel(average_frequencies_model);

    auto text_frequencies_model {new TextFrequenciesTableModel};
    text_frequencies_model->setSourceModel(&symbols_model);
    ui->TextFrequenciesTable->setModel(text_frequencies_model);
}

FrequencyAnalysis::~FrequencyAnalysis()
{
    delete ui;
}

void FrequencyAnalysis::on_TextLoadFromFileButton_clicked()
{
    QFileDialog file_dialog(this, "Выберите файл с текстом");
    file_dialog.setMimeTypeFilters({
        "text/plain",
        "application/octet-stream"
    });
    if (file_dialog.exec()) {
        qDebug() << file_dialog.selectedFiles();
        QFile file(file_dialog.selectedFiles().at(0));
        file.open(QFile::Text | QFile::ReadOnly);
        QString text {QString::fromUtf8(file.readAll())};
        ui->EncodedTextEdit->setPlainText(text);
        file.close();
    }
}

void FrequencyAnalysis::on_TextAnalyseButton_clicked()
{
    symbols_model.calculateFrequencies(ui->EncodedTextEdit->toPlainText());

    ui->ReplaceList->clear();
    ui->DecodedTextEdit->setPlainText(ui->EncodedTextEdit->toPlainText());
    ui->AutoReplaceButton->setEnabled(true);

    draw_histogram();
}

void FrequencyAnalysis::update_manual_replace_button()
{
    auto text_table {ui->TextFrequenciesTable};
    auto average_table {ui->AverageFrequenciesTable};
    auto from_index {text_table->selectionModel()->currentIndex()};
    auto to_index {average_table->selectionModel()->currentIndex()};
    if (from_index.isValid() and to_index.isValid()) {
        auto from_symbol {text_table->model()->data(
            text_table->model()->index(from_index.row(), 1), Qt::DisplayRole
        ).toString()};
        auto to_symbol {average_table->model()->data(
            average_table->model()->index(to_index.row(), 1), Qt::DisplayRole
        ).toString()};

        ui->ManualReplaceButton->setEnabled(true);
        ui->ManualReplaceButton->setText(
            "Заменить " + from_symbol + " на " + to_symbol
        );
    }
}

void FrequencyAnalysis::on_ManualReplaceButton_clicked()
{
    auto text_table {ui->TextFrequenciesTable};
    auto average_table {ui->AverageFrequenciesTable};
    auto from_index {text_table->selectionModel()->currentIndex()};
    auto to_index {average_table->selectionModel()->currentIndex()};
    if (from_index.isValid() and to_index.isValid()) {
        auto text {ui->DecodedTextEdit->toPlainText()};
        auto text_model {text_table->model()};
        auto average_model {average_table->model()};
        auto from_symbol_edit {text_model->data(text_model->index(from_index.row(), 1), Qt::EditRole).toChar()};
        auto to_symbol_edit {average_model->data(average_model->index(to_index.row(), 1), Qt::EditRole).toChar()};
        auto from_symbol_display {text_model->data(text_model->index(from_index.row(), 1), Qt::DisplayRole).toString()};
        auto to_symbol_display {average_model->data(average_model->index(to_index.row(), 1), Qt::DisplayRole).toString()};
        text.replace(from_symbol_edit, to_symbol_edit);
        ui->DecodedTextEdit->setPlainText(text);
        ui->ReplaceList->addItem(from_symbol_display + " => " + to_symbol_display);
    }
}

void FrequencyAnalysis::on_AverageFrequenciesTable_clicked(const QModelIndex&)
{
    this->update_manual_replace_button();
}

void FrequencyAnalysis::on_TextFrequenciesTable_clicked(const QModelIndex&)
{
    this->update_manual_replace_button();
}

void FrequencyAnalysis::on_AutoReplaceButton_clicked()
{
    auto text {ui->DecodedTextEdit->toPlainText()};
    auto replaceList {symbols_model.autoReplace(text)};

    ui->DecodedTextEdit->setPlainText(text);

    for (auto symbolsPair : replaceList) {
        auto fromDisplay {symbols_model.data(symbolsPair.first, 1, Qt::DisplayRole).toString()};
        auto toDisplay {symbols_model.data(symbolsPair.second, 1, Qt::DisplayRole).toString()};
        ui->ReplaceList->addItem(fromDisplay + " => " + toDisplay);
    }
}

void FrequencyAnalysis::draw_histogram()
{
    auto symbols {symbols_model.getAllSymbols()};
    auto barSet {new QBarSet("Относительная частота символа в тексте")};
    QStringList categories;
    double maxRelativeFrequency {0.0};
    for (auto& symbolInfo : symbols) {
        if (symbolInfo.absolute_frequency > 0) {
            *barSet << symbolInfo.relative_frequency;
            if (symbolInfo.relative_frequency > maxRelativeFrequency) {
                maxRelativeFrequency = symbolInfo.relative_frequency;
            }
            categories << symbols_model.data(symbolInfo, 1, Qt::DisplayRole).toString();
        }
    }

    auto series {new QBarSeries()};
    series->append(barSet);

    auto chart {new QChart()};
    chart->addSeries(series);

    auto axisX {new QBarCategoryAxis()};
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto axisY {new QValueAxis()};
    axisY->setRange(0.0, maxRelativeFrequency);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    ui->HistogramChart->setChart(chart);
}
