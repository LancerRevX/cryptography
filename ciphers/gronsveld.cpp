#include "ciphers.hpp"

#include <algorithm>

wstring gronsveld::encode(wstring const& message, vector<wstring> const& alphabets, vector<size_t> key) {
    if (key.size() == 0) {
        key.push_back(0);
    } else {
        for (auto number : key) {
            if (number >= 10) {
                throw InvalidKey();
            }
        }
    }

    size_t old_key_size = key.size();
    for (size_t i {old_key_size}; i < message.size(); i++) {
        key.push_back(key[i % old_key_size]);
    }

    wstring result(message.size(), 0);

    for (size_t i {0}; i < message.size(); i++) {
        for (auto& alphabet : alphabets) {
            size_t symbol_position {alphabet.find(message[i])};
            if (symbol_position != wstring::npos) {
                auto rotated_alphabet {alphabet};
                rotate(rotated_alphabet.begin(), rotated_alphabet.begin() + key[i] % rotated_alphabet.size(), rotated_alphabet.end());
                result[i] = rotated_alphabet[symbol_position];
                goto next_symbol;
            }
        }

        result[i] = message[i];
        next_symbol:;
    }

    return result;
}

wstring gronsveld::decode(wstring const& code, vector<wstring> const& alphabets, vector<size_t> key) {
    if (key.size() == 0) {
        key.push_back(0);
    } else {
        for (auto number : key) {
            if (number >= 10) {
                throw InvalidKey();
            }
        }
    }

    size_t old_key_size = key.size();
    for (size_t i {old_key_size}; i < code.size(); i++) {
        key.push_back(key[i % old_key_size]);
    }

    wstring result(code.size(), 0);

    for (size_t i {0}; i < code.size(); i++) {
        for (auto& alphabet : alphabets) {
            size_t symbol_position {alphabet.find(code[i])};
            if (symbol_position != wstring::npos) {
                auto rotated_alphabet {alphabet};
                rotate(rotated_alphabet.rbegin(), rotated_alphabet.rbegin() + key[i] % rotated_alphabet.size(), rotated_alphabet.rend());
                result[i] = rotated_alphabet[symbol_position];
                goto next_symbol;
            }
        }

        result[i] = code[i];
        next_symbol:;
    }

    return result;
}
