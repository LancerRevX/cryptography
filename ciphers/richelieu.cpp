#include "ciphers.hpp"

#include <algorithm>

wstring richelieu::encode(wstring const& message, vector<vector<size_t>> const& key) {
    size_t key_length {0};
    for (auto& segment : key) {
        key_length += segment.size();
        for (size_t i = 1; i <= segment.size(); i++) {
            if (find(segment.begin(), segment.end(), i) == segment.end()) {
                throw InvalidKeySegment();
            }
        }
    }
    if (key_length > message.length()) {
        throw KeyLongerThanMessage();
    }

    wstring result(message.length(), 0);
    size_t i {0};
    for (auto& segment : key) {
        for (size_t j {0}; j < segment.size(); j++) {
            result[i + segment[j] - 1] = message[i + j];
        }
        i += segment.size();
    }
    while (i < message.length()) {
        result[i] = message[i];
        i++;
    }
    return result;
}

wstring richelieu::decode(wstring const& code, vector<vector<size_t>> const& key) {
    size_t key_length {0};
    for (auto& segment : key) {
        key_length += segment.size();
        for (size_t i = 1; i <= segment.size(); i++) {
            if (find(segment.begin(), segment.end(), i) == segment.end()) {
                throw InvalidKeySegment();
            }
        }
    }
    if (key_length > code.length()) {
        throw KeyLongerThanMessage();
    }

    wstring result(code.length(), 0);
    size_t i {0};
    for (auto& segment : key) {
        for (size_t j {0}; j < segment.size(); j++) {
            result[i + j] = code[i + segment[j] - 1];
        }
        i += segment.size();
    }
    while (i < code.length()) {
        result[i] = code[i];
        i++;
    }
    return result;
}
