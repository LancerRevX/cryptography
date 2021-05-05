#include "ciphers.hpp"

#include <numeric>
#include <iostream>

#include "matrix/matrix.hpp"

wstring hill::encode(wstring const& message, wstring const& alphabet, vector<vector<int>> const& key) {
    if (key.size() != message.size()) {
        throw InvalidKey();
    }
    if (not is_square(key)) {
        throw InvalidKey();
    }

    if (not is_invertible(key, alphabet.size())) {
        throw KeyIsNotInvertible();
    }

    for (size_t i {0}; i < alphabet.size(); i++) {
        auto erased_alphabet {alphabet};
        erased_alphabet.erase(i);
        if (erased_alphabet.find(alphabet[i]) != wstring::npos) {
            throw InvalidAlphabet();
        }
    }

    for (auto symbol : message) {
        if (alphabet.find(symbol) == wstring::npos) {
            throw InvalidMessage();
        }
    }

    Matrix message_matrix(message.size());
    for (size_t i {0}; i < message.size(); i++) {
        message_matrix[i].resize(1);
        message_matrix[i][0] = alphabet.find(message[i]);
    }

    Matrix result_matrix {multiply(key, message_matrix)};
    wstring result(result_matrix.size(), 0);
    for (size_t i {0}; i < result.size(); i++) {
        result[i] = alphabet[result_matrix[i][0] % alphabet.size()];
    }
    return result;
}

wstring hill::decode(wstring const& message, wstring const& alphabet, vector<vector<int>> const& key) {
    if (key.size() != message.size()) {
        throw InvalidKey();
    }
    if (not is_square(key)) {
        throw InvalidKey();
    }

    if (not is_invertible(key, alphabet.size())) {
        throw KeyIsNotInvertible();
    }

    for (size_t i {0}; i < alphabet.size(); i++) {
        auto erased_alphabet {alphabet};
        erased_alphabet.erase(i);
        if (erased_alphabet.find(alphabet[i]) != wstring::npos) {
            throw InvalidAlphabet();
        }
    }

    for (auto symbol : message) {
        if (alphabet.find(symbol) == wstring::npos) {
            throw InvalidMessage();
        }
    }

    Matrix message_matrix(message.size());
    for (size_t i {0}; i < message.size(); i++) {
        message_matrix[i].resize(1);
        message_matrix[i][0] = alphabet.find(message[i]);
    }

    Matrix result_matrix {modular_multiply(modular_inverse(key, alphabet.size()), message_matrix, alphabet.size())};
    wstring result(result_matrix.size(), 0);
    for (size_t i {0}; i < result.size(); i++) {
        result[i] = alphabet[result_matrix[i][0] % alphabet.size()];
    }
    return result;
}
