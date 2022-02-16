#include "ciphers.hpp"

#include <algorithm>

wstring des::encode(wstring const& message, vector<bool> const& key) {
    if (key.size() != 64) {
        throw InvalidKey();
    }

    for (size_t i = 0; i < 64; i += 8) {
        int ones_number = 0;
        for (size_t j = 0; j < 8; j++) {
            ones_number += key[i + j];
        }
        if (ones_number % 2 == 0) {
            throw InvalidKey();
        }
    }

    vector<bool> message_bits {message_to_bits(message)};
    if (message_bits.size() % 64 != 0) {
        for (size_t i = 0; i < 64 - message_bits.size() % 64; i++) {
            message_bits.push_back(0);
        }
    }

    vector<vector<bool>> message_blocks;
    message_blocks.reserve(message_bits.size() / 64);
    for (size_t i = 0; i < message_bits.size() / 64; i++) {
        message_blocks.push_back(vector<bool>(message_bits.begin() + i*64, message_bits.begin() + i*64 + 63));
    }

    vector<vector<bool>> C(17), D(17);

    vector<size_t> const C0_replacement_table {
        56, 48, 40, 32, 24, 16, 8, 0, 57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35
    };
    vector<size_t> const D0_replacement_table {
        62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 60, 52, 44, 36, 28, 20, 12, 4, 27, 19, 11, 3
    };

    vector<size_t> const CiDi_shift_table {
        1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
    };

    C[0].reserve(28);
    for (size_t position : C0_replacement_table) {
        C[0].push_back(key[position]);
    }
    D[0].reserve(28);
    for (size_t position : D0_replacement_table) {
        D[0].push_back(key[position]);
    }

    for (size_t i = 1; i < C.size(); i++) {
        C[i] = C[i-1];
        rotate(C[i].begin(), C[i].begin() + CiDi_shift_table[i-1], C[i].end());
    }
    for (size_t i = 1; i < D.size(); i++) {
        D[i] = D[i-1];
        rotate(D[i].begin(), D[i].begin() + CiDi_shift_table[i-1], D[i].end());
    }

    vector<vector<bool>> k(16);
    vector<size_t> const k_replacement_table {
        13, 16, 10, 23, 0, 4, 2, 27, 14, 5, 20, 9, 22, 18, 11, 3,
        25, 7, 15, 6, 26, 19, 12, 1, 40, 51, 30, 36, 46, 54, 29, 39,
        50, 44, 32, 47, 43, 48, 38, 55, 33, 52, 45, 41, 49, 35, 28, 31
    };
    for (size_t i = 0; i < k.size(); i++) {
        vector<bool> CiDi {C[i+1]};
        CiDi.insert(CiDi.end(), D[i+1].begin(), D[i+1].end());
        k[i].resize(48);
        for (size_t j = 0; j < 48; j++) {
            k[i][j] = CiDi[k_replacement_table[j]];
        }
    }

    vector<size_t> const IP_replacement_table {
        57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7,
        56, 48, 40, 32, 24, 16, 8, 0, 58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6
    };

    vector<vector<bool>> result_blocks;
    result_blocks.reserve(message_blocks.size());
    for (vector<bool>& block : message_blocks) {
        vector<bool> IP(block.size());
        for (size_t i = 0; i < block.size(); i++) {
            IP[i] = block[IP_replacement_table[i]];
        }
        vector<bool> L(IP.begin(), IP.begin() + 31);
        vector<bool> R(IP.begin() + 32, IP.end() - 1);
        for (size_t i = 0; i < 16; i++) {
            vector<bool> new_L {R};
            vector<bool> new_R {exclusive_or(L, feistel_function(R, k[i]))};
        }
    }

    return L"Encoded message";
}

vector<bool> des::message_to_bits(wstring const& message) {
    vector<bool> result;
    result.reserve(message.size() * sizeof(wchar_t));
    for (wchar_t symbol : message) {
        for (size_t i = 1; i <= sizeof(wchar_t) * 8; i++) {
            result.push_back((symbol >> (sizeof(wchar_t) * 8 - i)) & 1);
        }
    }

    return result;
}

vector<bool> des::feistel_function(vector<bool> const& R, vector<bool> const& k) {
    if (R.size() != 32 or k.size() != 48) {
        throw exception();
    }

    vector<size_t> const E_extension_table {
        31, 0, 1, 2, 3, 4,
        3, 4, 5, 6, 7, 8,
        7, 8, 9, 10, 11, 12,
        11, 12, 13, 14, 15, 16,
        15, 16, 17, 18, 19, 20,
        19, 20, 21, 22, 23, 24,
        23, 24, 25, 26, 27, 28,
        27, 28, 29, 30, 31, 0
    };
    vector<bool> E(R.size());
    for (size_t i = 0; i < R.size(); i++) {
        E[i] = R[E_extension_table[i]];
    }

    vector<vector<uint8_t>> const S_transformation_tables {
        {
            14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
            1, 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
            2, 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
            3, 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
        }
    };

    vector<bool> E_xor_k {exclusive_or(E, k)};
    vector<vector<bool>> B(8);
    for (size_t i = 0; i < B.size(); i++) {
        B[i] = vector<bool>(E_xor_k.begin() + i*6, E_xor_k.begin() + i*6 + 7);
        size_t a = B[i][0] * 2 + B[i][5];
        size_t b = B[i][1] * 8 + B[i][2] * 4 + B[i][3] * 2 + B[i][4];
        uint8_t number = S_transformation_tables[i][a * 16 + b];
        B[i] = vector<bool>({
            bool(number & 1),
            bool(number >> 1 & 1),
            bool(number >> 2 & 1),
            bool(number >> 3 & 1)
        });
    }

    vector<bool> BB {B[0]};
    for (size_t i = 1; i < B.size(); i++) {
        BB.insert(BB.end(), B[i].begin(), B[i].end());
    }

    vector<size_t> const P_replacement_table {
        15, 6, 19, 20, 28, 11, 27, 16,
        0, 14, 22, 25, 4, 17, 30, 9,
        1, 7, 23, 13, 31, 26, 2, 8,
        18, 12, 29, 5, 21, 10, 3, 24
    };
    vector<bool> P(BB.size());
    for (size_t i = 0; i < BB.size(); i++) {
        P[i] = BB[P_replacement_table[i]];
    }

    return P;
}

vector<bool> des::exclusive_or(vector<bool> const& left, vector<bool> const& right) {
    if (left.size() != right.size()) {
        throw exception();
    }

    vector<bool> result(left.size());
    for (size_t i = 0; i < left.size(); i++) {
        result[i] = left[i] xor right[i];
    }
    return result;
}
