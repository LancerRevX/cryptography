#include "symbols_table_model.hpp"

SymbolsTableModel::SymbolsTableModel() : QAbstractTableModel()
{
    this->symbols = {
        SymbolInfo(Alphabet::common, L' ', 0.175),

        SymbolInfo(Alphabet::russian, L'А', 0.062),
        SymbolInfo(Alphabet::russian, L'Б', 0.014),
        SymbolInfo(Alphabet::russian, L'В', 0.038),
        SymbolInfo(Alphabet::russian, L'Г', 0.013),
        SymbolInfo(Alphabet::russian, L'Д', 0.025),
        SymbolInfo(Alphabet::russian, L'Е', 0.072),
        SymbolInfo(Alphabet::russian, L'Ж', 0.007),
        SymbolInfo(Alphabet::russian, L'З', 0.016),
        SymbolInfo(Alphabet::russian, L'И', 0.062),
        SymbolInfo(Alphabet::russian, L'Й', 0.010),
        SymbolInfo(Alphabet::russian, L'К', 0.028),
        SymbolInfo(Alphabet::russian, L'Л', 0.035),
        SymbolInfo(Alphabet::russian, L'М', 0.026),
        SymbolInfo(Alphabet::russian, L'Н', 0.053),
        SymbolInfo(Alphabet::russian, L'О', 0.090),
        SymbolInfo(Alphabet::russian, L'П', 0.023),
        SymbolInfo(Alphabet::russian, L'Р', 0.040),
        SymbolInfo(Alphabet::russian, L'С', 0.045),
        SymbolInfo(Alphabet::russian, L'Т', 0.053),
        SymbolInfo(Alphabet::russian, L'У', 0.021),
        SymbolInfo(Alphabet::russian, L'Ф', 0.002),
        SymbolInfo(Alphabet::russian, L'Х', 0.009),
        SymbolInfo(Alphabet::russian, L'Ц', 0.004),
        SymbolInfo(Alphabet::russian, L'Ч', 0.012),
        SymbolInfo(Alphabet::russian, L'Ш', 0.006),
        SymbolInfo(Alphabet::russian, L'Щ', 0.003),
        SymbolInfo(Alphabet::russian, L'Ъ', 0.014),
        SymbolInfo(Alphabet::russian, L'Ы', 0.016),
        SymbolInfo(Alphabet::russian, L'Э', 0.003),
        SymbolInfo(Alphabet::russian, L'Ю', 0.006),
        SymbolInfo(Alphabet::russian, L'Я', 0.018),

        SymbolInfo(Alphabet::english, L'A', 0.081),
        SymbolInfo(Alphabet::english, L'B', 0.016),
        SymbolInfo(Alphabet::english, L'C', 0.032),
        SymbolInfo(Alphabet::english, L'D', 0.036),
        SymbolInfo(Alphabet::english, L'E', 0.123),
        SymbolInfo(Alphabet::english, L'F', 0.023),
        SymbolInfo(Alphabet::english, L'G', 0.016),
        SymbolInfo(Alphabet::english, L'H', 0.051),
        SymbolInfo(Alphabet::english, L'I', 0.071),
        SymbolInfo(Alphabet::english, L'J', 0.001),
        SymbolInfo(Alphabet::english, L'K', 0.005),
        SymbolInfo(Alphabet::english, L'L', 0.040),
        SymbolInfo(Alphabet::english, L'M', 0.022),
        SymbolInfo(Alphabet::english, L'N', 0.072),
        SymbolInfo(Alphabet::english, L'O', 0.079),
        SymbolInfo(Alphabet::english, L'P', 0.023),
        SymbolInfo(Alphabet::english, L'Q', 0.002),
        SymbolInfo(Alphabet::english, L'R', 0.060),
        SymbolInfo(Alphabet::english, L'S', 0.066),
        SymbolInfo(Alphabet::english, L'T', 0.096),
        SymbolInfo(Alphabet::english, L'U', 0.031),
        SymbolInfo(Alphabet::english, L'V', 0.009),
        SymbolInfo(Alphabet::english, L'W', 0.020),
        SymbolInfo(Alphabet::english, L'X', 0.002),
        SymbolInfo(Alphabet::english, L'Y', 0.019),
        SymbolInfo(Alphabet::english, L'Z', 0.001),
    };
}

int SymbolsTableModel::rowCount(const QModelIndex&) const
{
    return this->symbols.size();
}

int SymbolsTableModel::columnCount(const QModelIndex&) const
{
    return 5;
}

QVariant SymbolsTableModel::data(const QModelIndex& index, int role) const
{
    if (index.row() >= symbols.size()) {
        return QVariant();
    } else {
        return data(symbols[index.row()], index.column(), role);
    }
}

QVariant SymbolsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (role) {
        case Qt::DisplayRole: {
            switch (orientation) {
                case Qt::Horizontal: {
                    switch (section) {
                        case 0: {
                            return "Алфавит";
                        }
                        case 1: {
                            return "Символ";
                        }
                        case 2: {
                            return "Средняя частота";
                        }
                        case 3: {
                            return "Отн. частота";
                        }
                        case 4: {
                            return "Абс. частота";
                        }
                        default: {
                            return QVariant();
                        }
                    }
                }
                case Qt::Vertical: {
                    return section + 1;
                }
                default: {}
            }
        }
        default: {
            return QVariant();
        }
    }
}

QVariant SymbolsTableModel::data(QChar symbol, int column, int role) const
{
    if (auto symbolInfo {getSymbolInfo(symbol)}) {
        return data(*symbolInfo, column, role);
    } else {
        return QVariant();
    }
}

QVariant SymbolsTableModel::data(const SymbolsTableModel::SymbolInfo& symbolInfo, int column, int role) const
{
    switch (role) {
        case Qt::EditRole:
        case Qt::DisplayRole:
            switch (column) {
                case 0: {
                    switch (symbolInfo.alphabet) {
                        case Alphabet::common: {
                            return "Общий";
                        }
                        case Alphabet::english: {
                            return "Английский";
                        }
                        case Alphabet::russian: {
                            return "Русский";
                        }
                        default: {}
                    }
                }
                case 1: {
                    if (symbolInfo.symbol == ' ' and role == Qt::DisplayRole) {
                        return "Пробел";
                    } else {
                        return symbolInfo.symbol;
                    }
                }
                case 2: {
                    return symbolInfo.average_frequency;
                }
                case 3: {
                    return symbolInfo.relative_frequency;
                }
                case 4: {
                    return symbolInfo.absolute_frequency;
                }
                default: {
                    return QVariant();
                }
            }
        default: {
            return QVariant();
        }
    }
}

void SymbolsTableModel::calculateFrequencies(const QString& text)
{
    for (auto& symbolInfo : this->symbols) {
        symbolInfo.absolute_frequency = 0;
        symbolInfo.relative_frequency = 0;
    }
    auto usedSymbolsNumber {0};

    for (auto textSymbol : text) {
        SymbolInfo* symbolInfo {getSymbolInfo(textSymbol)};
        if (symbolInfo) {
            symbolInfo->absolute_frequency += 1;
            usedSymbolsNumber += 1;
        }
    }

    if (usedSymbolsNumber > 0) {
        for (auto& symbolInfo : symbols) {
            symbolInfo.relative_frequency = (double) symbolInfo.absolute_frequency / usedSymbolsNumber;
        }
    }
}

QList<QPair<QChar, QChar>> SymbolsTableModel::autoReplace(QString& text) const
{
    QHash<QChar, QChar> replacements;
    QList<QPair<QChar, QChar>> replaceList;
    for (int i {0}; i < text.size(); i++) {
        if (replacements.contains(text[i])) {
            text[i] = replacements[text[i]];
        } else if (auto textSymbolInfo {getSymbolInfo(text[i])}) {
            QList<SymbolInfo> possibleReplacements;
            for (auto& listSymbolInfo : symbols) {
                if (
                    listSymbolInfo.alphabet == textSymbolInfo->alphabet and
                    not replacements.values().contains(listSymbolInfo.symbol)
                ) {
                    possibleReplacements.append(listSymbolInfo);
                }
            }

            double minDifference {abs(possibleReplacements[0].average_frequency - textSymbolInfo->relative_frequency)};
            int minDifferenceIndex {0};
            for (int j {1}; j < possibleReplacements.size(); j++) {
                double difference {abs(possibleReplacements[j].average_frequency - textSymbolInfo->relative_frequency)};
                if (difference < minDifference) {
                    minDifference = difference;
                    minDifferenceIndex = j;
                }
            }
            replacements.insert(text[i], possibleReplacements[minDifferenceIndex].symbol);
            replaceList.append(QPair<QChar, QChar>(text[i], possibleReplacements[minDifferenceIndex].symbol));
            text[i] = replacements[text[i]];
        }
    }

    return replaceList;
}

const SymbolsTableModel::SymbolInfo* SymbolsTableModel::getSymbolInfo(QChar symbol) const
{
    auto symbolInfoIterator {std::find_if(symbols.begin(), symbols.end(), [symbol](SymbolInfo symbolInfo) {
        return symbolInfo.symbol == symbol;
    })};
    if (symbolInfoIterator == symbols.end()) {
        return nullptr;
    } else {
        return &symbols[symbolInfoIterator - symbols.begin()];
    }
}

SymbolsTableModel::SymbolInfo* SymbolsTableModel::getSymbolInfo(QChar symbol)
{
    auto symbolInfoIterator {std::find_if(symbols.begin(), symbols.end(), [symbol](SymbolInfo symbolInfo) {
        return symbolInfo.symbol == symbol;
    })};
    if (symbolInfoIterator == symbols.end()) {
        return nullptr;
    } else {
        return &symbols[symbolInfoIterator - symbols.begin()];
    }
}

const QVector<SymbolsTableModel::SymbolInfo>& SymbolsTableModel::getAllSymbols() const
{
    return symbols;
}

bool AverageFrequenciesTableModel::filterAcceptsColumn(int source_column, const QModelIndex&) const
{
    return source_column >= 0 and source_column <= 2;
}

bool TextFrequenciesTableModel::filterAcceptsColumn(int source_column, const QModelIndex&) const
{
    return (source_column >= 0 and source_column <= 1) or (source_column >= 3 and source_column <= 4);
}
