#include "ciphers.hpp"

wstring vernam::encode(wstring const& message, wstring key) {
    if (key.size() == 0) {
        key = message;
    } else {
        for (size_t i {key.size()}; i < message.size(); i++) {
            key.push_back(key[i % key.size()]);
        }
    }

    wstring result(message.size(), 0);
    for (size_t i {0}; i < message.size(); i++) {
        result[i] = message[i] ^ key[i];
    }
    return result;
}
