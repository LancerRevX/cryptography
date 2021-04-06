#pragma once

#include <string>
#include <vector>

using namespace std;

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

namespace caesar_cipher {
    wstring encode(wstring const& message, int key, vector<wstring> const& alphabets);
    wstring decode(wstring const& message, int key, vector<wstring> const& alphabets);
}

namespace cardan_grille {
    class GrilleAndCodeDoNotMatch : public exception {};
    class GrilleNotSquare : public exception {};
    class MessageLongerThanHolesNumber: public exception {};
    class MessageLengthNotEqualToCellsNumber: public exception {};

    vector<vector<wchar_t>> encode(wstring const& message, vector<vector<bool>> const& grille, bool junk);
    wstring decode(vector<vector<wchar_t>> const& code, vector<vector<bool>> const& grille, bool junk);
    vector<vector<bool>> get_random_grille(size_t size);
}
