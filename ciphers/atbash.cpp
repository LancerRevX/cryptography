#include "ciphers.hpp"

#include <regex>

std::wstring atbash::encode(const std::wstring& message) {
    if (!std::regex_match(message, std::wregex(L"^[а-яёА-ЯЁa-zA-Z .,!?\n]+$"))) {
        throw std::runtime_error("A message can contain only cyrillic and latin letters, "
                                 "spaces, dots, commas, newline characters, exclamation and question marks.");
    }

    auto result = std::wstring();
    for (auto symbol : message) {
        if (std::regex_match(std::wstring(1, symbol), std::wregex(L"[ .,!?ёЁ\n]"))) {
            result += symbol;
        } else if (std::regex_match(std::wstring(1, symbol), std::wregex(L"[а-я]"))) {
            result += L'а' + L'я' - symbol;
        } else if (std::regex_match(std::wstring(1, symbol), std::wregex(L"[А-Я]"))) {
            result += L'А' + L'Я' - symbol;
        } else if (std::regex_match(std::wstring(1, symbol), std::wregex(L"[a-z]"))) {
            result += L'a' + L'z' - symbol;
        } else if (std::regex_match(std::wstring(1, symbol), std::wregex(L"[A-Z]"))) {
            result += L'A' + L'Z' - symbol;
        }
    }
    return result;
}
