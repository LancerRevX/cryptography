#include "ciphers.hpp"

#include <optional>
#include <iostream>
#include <algorithm>

std::optional<std::pair<size_t, size_t>> find_symbol_in_square(
    wchar_t symbol,
    std::vector<std::vector<std::wstring>> const& square
) {
    for (size_t i = 0; i < square.size(); i++) {
        for (size_t j = 0; j < square[i].size(); j++) {
            if (square[i][j].find(symbol) != std::string::npos) {
                return std::make_pair(i, j);
            }
        }
    }
    return std::nullopt;
}

std::wstring polybius_square::method_1::encode(
    std::wstring const& message,
    std::vector<std::vector<std::wstring>> const& square
) {
    std::wstring result;
    for (auto symbol : message) {
        auto symbol_position = find_symbol_in_square(symbol, square);
        if (symbol_position) {
            auto i = symbol_position.value().first;
            auto j = symbol_position.value().second;
            do {
                i += 1;
                if (i == square.size()) {
                    i = 0;
                }
            } while (square[i][j].empty());
            result += square[i][j][0];
        } else {
            result += symbol;
        }
    }
    return result;
}

std::wstring polybius_square::method_1::decode(
    std::wstring const& code,
    std::vector<std::vector<std::wstring>> const& square
) {
    std::wstring result;
    for (auto symbol : code) {
        auto symbol_position = find_symbol_in_square(symbol, square);
        if (symbol_position) {
            auto i = symbol_position.value().first;
            auto j = symbol_position.value().second;
            do {
                i = i == 0 ?
                    square.size() - 1 :
                    i - 1;
            } while (square[i][j].empty());
            result += square[i][j][0];
        } else {
            result += symbol;
        }
    }
    return result;
}

std::wstring polybius_square::method_2::encode(
    std::wstring const& message,
    std::vector<std::vector<std::wstring>> const& square
) {
    std::vector<std::optional<wchar_t>> code(message.length());
    std::vector<size_t> coordinates;
    for (size_t i = 0; i < message.length(); i++) {
        auto symbol_position {find_symbol_in_square(message[i], square)};
        if (symbol_position) {
            code[i] = std::nullopt;
            coordinates.insert(coordinates.begin() + coordinates.size()/2, symbol_position.value().second);
            coordinates.push_back(symbol_position.value().first);
        } else {
            code[i] = message[i];
        }
    }
    std::wstring result;
    size_t i = 0;
    for (auto& symbol : code) {
        if (symbol) {
            result += symbol.value();
        } else {
            result += square[coordinates[i + 1]][coordinates[i]][0];
            i += 2;
        }
    }

    return result;
}

std::wstring polybius_square::method_2::decode(
    std::wstring const& code,
    std::vector<std::vector<std::wstring>> const& square
) {
    std::vector<std::optional<wchar_t>> message(code.length());
    std::vector<size_t> coordinates;
    for (size_t i = 0; i < code.length(); i++) {
        auto symbol_position {find_symbol_in_square(code[i], square)};
        if (symbol_position) {
            message[i] = std::nullopt;
            coordinates.push_back(symbol_position.value().second);
            coordinates.push_back(symbol_position.value().first);
        } else {
            message[i] = code[i];
        }
    }
    std::wstring result;
    size_t i = 0;
    for (auto& symbol : message) {
        if (symbol) {
            result += symbol.value();
        } else {
            result += square[coordinates[i + coordinates.size()/2]][coordinates[i]][0];
            i += 1;
        }
    }

    return result;
}

std::wstring polybius_square::method_3::encode(
    std::wstring const& message,
    std::vector<std::vector<std::wstring>> const& square
) {
    std::vector<std::optional<wchar_t>> code(message.length());
    std::vector<size_t> coordinates;
    for (size_t i = 0; i < message.length(); i++) {
        auto symbol_position {find_symbol_in_square(message[i], square)};
        if (symbol_position) {
            code[i] = std::nullopt;
            coordinates.insert(coordinates.begin() + coordinates.size()/2, symbol_position.value().second);
            coordinates.push_back(symbol_position.value().first);
        } else {
            code[i] = message[i];
        }
    }
    std::wstring result;
    size_t i = 0;
    if (coordinates.size()) {
        std::rotate(coordinates.begin(), coordinates.begin() + 1, coordinates.end());
    }
    for (auto& symbol : code) {
        if (symbol) {
            result += symbol.value();
        } else {
            result += square[coordinates[i + 1]][coordinates[i]][0];
            i += 2;
        }
    }

    return result;
}

std::wstring polybius_square::method_3::decode(
    std::wstring const& code,
    std::vector<std::vector<std::wstring>> const& square
) {
    std::vector<std::optional<wchar_t>> message(code.length());
    std::vector<size_t> coordinates;
    for (size_t i = 0; i < code.length(); i++) {
        auto symbol_position {find_symbol_in_square(code[i], square)};
        if (symbol_position) {
            message[i] = std::nullopt;
            coordinates.push_back(symbol_position.value().second);
            coordinates.push_back(symbol_position.value().first);
        } else {
            message[i] = code[i];
        }
    }
    std::wstring result;
    size_t i = 0;
    if (coordinates.size()) {
        std::rotate(coordinates.rbegin(), coordinates.rbegin() + 1, coordinates.rend());
    }
    for (auto& symbol : message) {
        if (symbol) {
            result += symbol.value();
        } else {
            result += square[coordinates[i + coordinates.size()/2]][coordinates[i]][0];
            i += 1;
        }
    }

    return result;
}
