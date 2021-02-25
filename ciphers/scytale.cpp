#include "ciphers.hpp"

std::wstring scytale::encode(const std::wstring& message, size_t m, size_t n) {
    std::wstring result;
    for (size_t start = 0; start < n; start += 1) {
        for (size_t i = start; i < m * n; i += n) {
            result += i < message.length() ? message[i] : '*';
        }
    }
    return result;
}

std::wstring scytale::decode(const std::wstring& message, size_t m, size_t n) {
    std::wstring result(m * n, 0);
    for (size_t i = 0; i < m; i += 1) {
        for (size_t j = 0; j < n; j += 1) {
            result[j + i*n] = message[i + j*m];
        }
    }
    return result;
}
