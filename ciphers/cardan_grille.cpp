#include "ciphers.hpp"

#include <optional>

vector<vector<bool>> rotate_grille_clockwise(vector<vector<bool>> const& grille, int rotation) {
    vector<vector<bool>> result(grille);
    size_t n = grille.size();
    for (int _ = 0; _ < rotation; _++) {
        for (size_t i = 0; i < n / 2; i++) {
            for (size_t j = i; j < n - i - 1; j++) {
                bool tmp = result[i][j];
                result[i][j] = result[n - 1 - j][i];
                result[n - 1 - j][i] = result[n - 1 - i][n - 1 - j];
                result[n - 1 - i][n - 1 - j] = result[j][n - 1 - i];
                result[j][n - 1 - i] = tmp;
            }
        }
    }
    return result;
}

vector<vector<wchar_t>> cardan_grille::encode(
    wstring const& message,
    vector<vector<bool>> const& grille,
    bool junk
) {
    size_t holes_number = 0;
    for (auto& row : grille) {
        if (row.size() != grille.size()) {
            throw GrilleNotSquare();
        }
        for (auto cell : row) {
            if (cell) {
                holes_number += 1;
            }
        }
    }

    if (junk and message.length() > holes_number*4) {
        throw MessageLongerThanHolesNumber();
    } else if (not junk and message.length() != holes_number*4) {
        throw MessageLengthNotEqualToHolesNumber();
    }

    vector<vector<optional<wchar_t>>> code(grille.size());
    for (auto& row : code) {
        row.assign(grille.size(), nullopt);
    }

    auto rotated_grille {grille};

    size_t message_index = 0;
    for (int rotation = 0; rotation < 4; rotation++) {
        auto rotated_grille {rotate_grille_clockwise(grille, rotation)};

        for (size_t i = 0; i < rotated_grille.size(); i++) {
            for (size_t j = 0; j < rotated_grille[i].size(); j++) {
                if (rotated_grille[i][j]) {
                    if (code[i][j] != nullopt) {
                        throw GrilleOverlaps();
                    }
                    if (message_index < message.length()) {
                        code[i][j] = message[message_index];
                        message_index += 1;
                    }
                }
            }
        }
    }

    vector<vector<wchar_t>> result(code.size());
    for (size_t i = 0; i < code.size(); i++) {
        result[i].resize(code[i].size());
        for (size_t j = 0; j < code[i].size(); j++) {
            if (junk and code[i][j] == nullopt) {
                static wstring const junk_characters = L"aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZаАбБвВгГдДеЕёЁжЖзЗиИйЙкКлЛмМнНоОпПрРсСтТуУфФхХцЦчЧшШщЩъЪыЫьЬэЭюЮяЯ1234567890.,!? _=-+/*";
                code[i][j] = junk_characters[rand() % junk_characters.length()];
            }
            result[i][j] = code[i][j].value();
        }
    }
    return result;
}

wstring cardan_grille::decode(
    vector<vector<wchar_t>> const& code,
    vector<vector<bool>> const& grille
) {
    if (code.size() != grille.size()) {
        throw GrilleAndCodeDoNotMatch();
    }
    for (size_t i = 0; i < code.size(); i++) {
        if (grille[i].size() != grille.size()) {
            throw GrilleNotSquare();
        }
        if (code[i].size() != grille.size()) {
            throw GrilleAndCodeDoNotMatch();
        }
    }
    wstring result;
    auto rotated_grille {grille};
    for (int rotation = 0; rotation < 4; rotation++) {
        auto rotated_grille {rotate_grille_clockwise(grille, rotation)};

        for (size_t i = 0; i < rotated_grille.size(); i++) {
            for (size_t j = 0; j < rotated_grille[i].size(); j++) {
                if (rotated_grille[i][j]) {
                    result += code[i][j];
                }
            }
        }
    }

    return result;
}
