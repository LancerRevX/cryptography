#include "ciphers.hpp"

#include <algorithm>

vector<vector<wstring>> playfair::get_encoding_matrix(
    vector<vector<wstring>> const& alphabet,
    wstring key
) {
    size_t alphabet_width {alphabet[0].size()};
    for (size_t i {1}; i < alphabet.size(); i++) {
        if (alphabet[i].size() != alphabet_width) {
            throw InvalidAlphabet();
        }
    }

    vector<wstring> alphabet_one_dimensional;
    alphabet_one_dimensional.reserve(alphabet.size() * alphabet_width);
    wstring alphabet_string;
    alphabet_string.reserve(alphabet.size() * alphabet_width);
    for (auto& row : alphabet) {
        for (auto& symbols : row) {
            alphabet_string += symbols;
            alphabet_one_dimensional.push_back(symbols);
        }
    }

    for (size_t i {0}; i < alphabet_string.size(); i++) {
        auto alphabet_string_erased {alphabet_string};
        alphabet_string_erased.erase(i, 1);
        if (alphabet_string_erased.find(alphabet_string[i]) != wstring::npos) {
            throw InvalidAlphabet();
        }
    }

    for (auto symbol : key) {
        if (alphabet_string.find(symbol) == wstring::npos) {
            throw InvalidKey();
        }
    }

    vector<vector<wstring>> encoding_matrix(alphabet.size());
    for (size_t i {0}; i < encoding_matrix.size(); i++) {
        encoding_matrix[i].resize(alphabet_width);
        for (size_t j {0}; j < encoding_matrix[i].size(); j++) {
            if (key.size() > 0) {
                for (auto& cell : alphabet_one_dimensional) {
                    if (cell.find(key[0]) != wstring::npos) {
                        encoding_matrix[i][j] = cell;
                        for (auto symbol : cell) {
                            key.erase(remove(key.begin(), key.end(), symbol), key.end());
                        }
                        alphabet_one_dimensional.erase(
                            remove(
                                alphabet_one_dimensional.begin(),
                                alphabet_one_dimensional.end(),
                                cell
                                ),
                            alphabet_one_dimensional.end()
                            );
                        break;
                    }
                }
            } else {
                encoding_matrix[i][j] = alphabet_one_dimensional[0];
                alphabet_one_dimensional.erase(alphabet_one_dimensional.begin());
            }
        }
    }

    return encoding_matrix;
}

vector<pair<wchar_t, wchar_t>> playfair::get_digrams(wstring const& message, wchar_t stub) {
    vector<pair<wchar_t, wchar_t>> digrams;
    digrams.reserve(message.size() / 2);
    for (size_t i {0}; i < message.size(); i += 2) {
        pair digram(message[i], 0);
        if (i < message.size() - 1) {
            if (digram.first != message[i + 1]) {
                digram.second = message[i + 1];
            } else {
                digram.second = stub;
                i -= 1;
            }
        } else {
            digram.second = stub;
        }
        digrams.push_back(digram);
    }
    return digrams;
}

wstring playfair::encode(
    wstring message,
    vector<vector<wstring>> const& alphabet,
    wstring key,
    wchar_t stub
) {
    auto encoding_matrix {get_encoding_matrix(alphabet, key)};

    wstring alphabet_string;
    alphabet_string.reserve(alphabet.size() * alphabet[0].size());
    for (auto& row : alphabet) {
        for (auto& cell : row) {
            alphabet_string += cell;
        }
    }

    if (alphabet_string.find(stub) == wstring::npos) {
        throw InvalidStub();
    }

    for (auto symbol : message) {
        if (alphabet_string.find(symbol) == wstring::npos) {
            throw InvalidMessage();
        }
    }

    auto digrams {get_digrams(message, stub)};

    wstring result;
    result.reserve(digrams.size() * 2);
    for (auto& digram : digrams) {
        size_t first_x = 0, first_y = 0;
        size_t second_x = 0, second_y = 0;
        for (size_t i {0}; i < encoding_matrix.size(); i++) {
            for (size_t j {0}; j < encoding_matrix[i].size(); j++) {
                if (encoding_matrix[i][j].find(digram.first) != wstring::npos) {
                    first_x = i; first_y = j;
                }
                if (encoding_matrix[i][j].find(digram.second) != wstring::npos) {
                    second_x = i; second_y = j;
                }
            }
        }
        if (first_x == second_x) {
            first_y = first_y < encoding_matrix[first_x].size() - 1 ?
                first_y + 1 : 0;
            second_y = second_y < encoding_matrix[second_x].size() - 1 ?
                second_y + 1 : 0;
        } else if (first_y == second_y) {
            first_x = first_x < encoding_matrix.size() - 1 ?
                first_x + 1 : 0;
            second_x = second_x < encoding_matrix.size() - 1 ?
                second_x + 1 : 0;
        } else {
            auto tmp = first_y;
            first_y = second_y;
            second_y = tmp;
        }
        result += encoding_matrix[first_x][first_y][0];
        result += encoding_matrix[second_x][second_y][0];
    }

    return result;
}

wstring playfair::decode(
    wstring message,
    vector<vector<wstring>> const& alphabet,
    wstring const& key,
    wchar_t stub
) {
    auto encoding_matrix {get_encoding_matrix(alphabet, key)};

    wstring alphabet_string;
    alphabet_string.reserve(alphabet.size() * alphabet[0].size());
    for (auto& row : alphabet) {
        for (auto& cell : row) {
            alphabet_string += cell;
        }
    }

    if (alphabet_string.find(stub) == wstring::npos) {
        throw InvalidStub();
    }

    for (auto symbol : message) {
        if (alphabet_string.find(symbol) == wstring::npos) {
            throw InvalidMessage();
        }
    }

    auto digrams {get_digrams(message, stub)};

    wstring result;
    result.reserve(digrams.size() * 2);
    for (auto& digram : digrams) {
        size_t first_x = 0, first_y = 0;
        size_t second_x = 0, second_y = 0;
        for (size_t i {0}; i < encoding_matrix.size(); i++) {
            for (size_t j {0}; j < encoding_matrix[i].size(); j++) {
                if (encoding_matrix[i][j].find(digram.first) != wstring::npos) {
                    first_x = i; first_y = j;
                }
                if (encoding_matrix[i][j].find(digram.second) != wstring::npos) {
                    second_x = i; second_y = j;
                }
            }
        }
        if (first_x == second_x) {
            first_y = first_y > 0 ?
                first_y - 1 : encoding_matrix[first_x].size() - 1;
            second_y = second_y > 0 ?
                second_y - 1 : encoding_matrix[first_x].size() - 1;
        } else if (first_y == second_y) {
            first_x = first_x > 0 ?
                first_x - 1 : encoding_matrix.size() - 1;
            second_x = second_x > 0 ?
                second_x - 1 : encoding_matrix.size() - 1;
        } else {
            auto tmp = first_y;
            first_y = second_y;
            second_y = tmp;
        }
        result += encoding_matrix[first_x][first_y][0];
        result += encoding_matrix[second_x][second_y][0];
    }

    return result;
}
