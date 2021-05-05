#include "ciphers.hpp"

#include <algorithm>

wstring vigenere::encode(wstring const& message, wstring const& alphabet, wstring key) {
    if (key.size() == 0) {
        throw InvalidKey();
    }
    for (auto symbol : key) {
        if (alphabet.find(symbol) == wstring::npos) {
            throw InvalidKey();
        }
    }

    size_t old_key_size = key.size();
    for (size_t i {old_key_size}; i < message.size(); i++) {
        key.push_back(key[i % old_key_size]);
    }

    wstring result(message.size(), 0);
    for (size_t i {0}; i < message.size(); i++) {
        auto message_symbol_position {alphabet.find(message[i])};
        if (message_symbol_position != wstring::npos) {
            auto key_symbol_position {alphabet.find(key[i])};
            auto rotated_alphabet {alphabet};
            rotate(rotated_alphabet.begin(), rotated_alphabet.begin() + key_symbol_position, rotated_alphabet.end());
            result[i] = rotated_alphabet[message_symbol_position];
        } else {
            result[i] = message[i];
        }
    }
    return result;
}

wstring vigenere::decode(wstring const& code, wstring const& alphabet, wstring key) {
    if (key.size() == 0) {
        throw InvalidKey();
    }
    for (auto symbol : key) {
        if (alphabet.find(symbol) == wstring::npos) {
            throw InvalidKey();
        }
    }

    size_t old_key_size = key.size();
    for (size_t i {old_key_size}; i < code.size(); i++) {
        key.push_back(key[i % old_key_size]);
    }

    wstring result(code.size(), 0);
    for (size_t i {0}; i < code.size(); i++) {
        auto code_symbol_position {alphabet.find(code[i])};
        if (code_symbol_position != wstring::npos) {
            auto key_symbol_position {alphabet.find(key[i])};
            auto rotated_alphabet {alphabet};
            rotate(rotated_alphabet.rbegin(), rotated_alphabet.rbegin() + key_symbol_position, rotated_alphabet.rend());
            result[i] = rotated_alphabet[code_symbol_position];
        } else {
            result[i] = code[i];
        }
    }
    return result;
}
