#include "ciphers.hpp"

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

    if (junk && message.length() > holes_number*4) {
        throw MessageLongerThanHolesNumber();
    } else if (!junk && message.length() != grille.size()*grille.size()) {
        throw MessageLengthNotEqualToCellsNumber();
    }

    return vector<vector<wchar_t>>();
}
