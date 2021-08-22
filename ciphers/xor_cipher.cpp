#include "ciphers.hpp"

wstring xor_cipher::encode(wstring const& message, wstring const& key) {
    if (key.length() < message.length()) {
        throw KeyDoesNotMatchMessage();
    }

    wstring result(message.length(), 0);
    for (size_t i {0}; i < message.length(); i++) {
        result[i] = message[i] ^ key[i];
    }
    return result;
}

wstring xor_cipher::decode(wstring const& code, wstring const& key) {
    if (key.length() < code.length()) {
        throw KeyDoesNotMatchMessage();
    }

    wstring result(code.length(), 0);
    for (size_t i {0}; i < code.length(); i++) {
        result[i] = code[i] ^ key[i];
    }
    return result;
}

wstring xor_cipher::generate_key(size_t length, wchar_t seed, wchar_t multiplier, wchar_t increment) {
    wstring result(length, 0);
    wchar_t current_value {seed};
    for (size_t i {0}; i < length; i++) {
        result[i] = current_value * multiplier + increment;
        current_value = result[i];
    }
    return result;
}
