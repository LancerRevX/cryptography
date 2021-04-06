#include "ciphers.hpp"

#include <algorithm>
#include <cmath>

wstring caesar_cipher::encode(wstring const& message, int key, vector<wstring> const& alphabets) {
    wstring result;
    vector<wstring> shifted_alphabets = alphabets;
    for (auto& alphabet : shifted_alphabets) {
        if (key < 0) {
            rotate(alphabet.rbegin(), alphabet.rbegin() + (abs(key) % alphabet.length()), alphabet.rend());
        } else {
            rotate(alphabet.begin(), alphabet.begin() + (key % alphabet.length()), alphabet.end());
        }
    }
    for (auto symbol : message) {
        size_t symbol_position = string::npos;
        for (size_t i = 0; i < alphabets.size(); i++) {
            symbol_position = alphabets[i].find(symbol);
            if (symbol_position != string::npos) {
                result += shifted_alphabets[i][symbol_position];
                break;
            }
        }
        if (symbol_position == string::npos) {
            result += symbol;
        }
    }
    return result;
}

wstring caesar_cipher::decode(wstring const& message, int key, vector<wstring> const& alphabets) {
    return caesar_cipher::encode(message, -key, alphabets);
}
