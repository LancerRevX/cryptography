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
    class MessageLongerThanHolesNumber : public exception {};
    class HolesNumberDoesntMatchGrilleSize : public exception {};
    class MessageLengthNotEqualToGrilleSize : public exception {};
    class GrilleOverlaps : public exception {};

    vector<vector<wchar_t>> encode(wstring const& message, vector<vector<bool>> const& grille, bool junk);
    wstring decode(vector<vector<wchar_t>> const& code, vector<vector<bool>> const& grille);
}

namespace richelieu {
    class KeyLongerThanMessage : public exception {};
    class InvalidKeySegment : public exception {};

    wstring encode(wstring const& message, vector<vector<size_t>> const& key);
    wstring decode(wstring const& code, vector<vector<size_t>> const& key);
}

namespace alberti_disk {
    class DisksDontMatch : public exception {};
    wstring encode(
        wstring const& message,
        wstring const& outer_disk,
        wstring inner_disk,
        int spin_step
    );
    wstring decode(
        wstring const& code,
        wstring const& outer_disk,
        wstring inner_disk,
        int spin_step
    );
}

namespace gronsveld {
    class InvalidKey : public exception {};

    wstring encode(wstring const& message, vector<wstring> const& alphabets, vector<size_t> key);
    wstring decode(wstring const& code, vector<wstring> const& alphabets, vector<size_t> key);
}

namespace vigenere {
    class InvalidKey : public exception {};

    wstring encode(wstring const& message, wstring const& alphabet, wstring key);
    wstring decode(wstring const& code, wstring const& alphabet, wstring key);
}

namespace playfair {
    class InvalidAlphabet : public exception {};
    class InvalidMessage : public exception {};
    class InvalidKey : public exception {};
    class InvalidStub : public exception {};

    vector<vector<wstring>> get_encoding_matrix(
        vector<vector<wstring>> const& alphabet,
        wstring key
    );
    vector<pair<wchar_t, wchar_t>> get_digrams(wstring const& message, wchar_t stub);
    wstring encode(
        wstring message,
        vector<vector<wstring>> const& alphabet,
        wstring key,
        wchar_t stub
    );
    wstring decode(
        wstring code,
        vector<vector<wstring>> const& alphabet,
        wstring const& key,
        wchar_t stub
    );
}

namespace hill {
    class InvalidMessage : public exception {};
    class InvalidAlphabet : public exception {};
    class InvalidKey : public exception {};
    class KeyIsNotInvertible : public exception {};

    wstring encode(wstring const& message, wstring const& alphabet, vector<vector<int>> const& key);
    wstring decode(wstring const& code, wstring const& alphabet, vector<vector<int>> const& key);
}

namespace vernam {
    wstring encode(wstring const& message, wstring key);
}

namespace xor_cipher {
    class KeyDoesNotMatchMessage : public exception {};

    wstring encode(wstring const& message, wstring const& key);
    wstring decode(wstring const& code, wstring const& key);
    wstring generate_key(size_t length, wchar_t seed, wchar_t multiplier, wchar_t increment);
}

namespace des {
    class InvalidKey : public exception {};

    wstring encode(wstring const& message, vector<bool> const& key);

    vector<bool> message_to_bits(wstring const& message);
    vector<bool> feistel_function(vector<bool> const& R, vector<bool> const& k);
    vector<bool> exclusive_or(vector<bool> const& left, vector<bool> const& right);
}
