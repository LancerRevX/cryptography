#ifndef SYMBOLSTABLEMODEL_HPP
#define SYMBOLSTABLEMODEL_HPP

#include <QAbstractTableModel>
#include <QSortFilterProxyModel>

class SymbolsTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    enum class Alphabet {
        no_alphabet, common, russian, english
    };

    struct SymbolInfo {
        SymbolInfo() {

        }
        SymbolInfo(Alphabet alphabet, QChar symbol, double average_frequency)
            : alphabet(alphabet), symbol(symbol), average_frequency(average_frequency)
        {
            relative_frequency = 0.0;
            absolute_frequency = 0;
        }
        Alphabet alphabet;
        QChar symbol;
        double average_frequency;
        double relative_frequency;
        int absolute_frequency;
    };

    SymbolsTableModel();
    virtual int rowCount(QModelIndex const& parent = QModelIndex()) const override;
    virtual int columnCount(QModelIndex const& parent = QModelIndex()) const override;
    virtual QVariant data(QModelIndex const& index, int role = Qt::DisplayRole) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QVariant data(QChar symbol, int column, int role = Qt::DisplayRole) const;
    QVariant data(SymbolInfo const&, int column, int role = Qt::DisplayRole) const;
    void calculateFrequencies(QString const& text);
    QList<QPair<QChar, QChar>> autoReplace(QString& text) const;

    SymbolInfo const* getSymbolInfo(QChar symbol) const;
    SymbolInfo* getSymbolInfo(QChar symbol);
    QVector<SymbolInfo> const& getAllSymbols() const;

private:
    QVector<SymbolInfo> symbols;
};

class AverageFrequenciesTableModel : public QSortFilterProxyModel {
    virtual bool filterAcceptsColumn(int source_column, const QModelIndex&) const override;
};

class TextFrequenciesTableModel : public QSortFilterProxyModel {
    virtual bool filterAcceptsColumn(int source_column, const QModelIndex&) const override;
};

#endif // SYMBOLSTABLEMODEL_HPP
