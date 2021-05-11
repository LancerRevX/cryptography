#ifndef FREQUENCYANALYSIS_HPP
#define FREQUENCYANALYSIS_HPP

#include <QWidget>

#include "symbols_table_model.hpp"

namespace Ui {
    class FrequencyAnalysis;
}

class FrequencyAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit FrequencyAnalysis(QWidget *parent = nullptr);
    ~FrequencyAnalysis();

private slots:
    void on_TextLoadFromFileButton_clicked();

    void on_TextAnalyseButton_clicked();

    void on_ManualReplaceButton_clicked();

    void on_AverageFrequenciesTable_clicked(const QModelIndex &index);

    void on_TextFrequenciesTable_clicked(const QModelIndex &index);

    void on_AutoReplaceButton_clicked();

private:
    Ui::FrequencyAnalysis *ui;

    void draw_histogram();
    void update_manual_replace_button();

    SymbolsTableModel symbols_model;
};

#endif // FREQUENCYANALYSIS_HPP
