#pragma once

#include <string>
#include <vector>

namespace atbash {
    std::wstring encode(const std::wstring& message);
}

namespace scytale {
    std::wstring encode(const std::wstring& message, size_t m, size_t n);
    std::wstring decode(const std::wstring& message, size_t m, size_t n);
}

namespace polybius_square {
    namespace method_1 {
        std::wstring encode(
            const std::wstring& message,
            const std::vector<std::vector<std::wstring>>& square
        );
        std::wstring decode(
            const std::wstring& message,
            const std::vector<std::vector<std::wstring>>& square
        );
    }

    namespace method_2 {
        std::wstring encode(
            const std::wstring& message,
            const std::vector<std::vector<std::wstring>>& square
        );
        std::wstring decode(
            const std::wstring& message,
            const std::vector<std::vector<std::wstring>>& square
        );
    }

    namespace method_3 {
        std::wstring encode(
            const std::wstring& message,
            const std::vector<std::vector<std::wstring>>& square
        );
        std::wstring decode(
            const std::wstring& message,
            const std::vector<std::vector<std::wstring>>& square
        );
    }
}
