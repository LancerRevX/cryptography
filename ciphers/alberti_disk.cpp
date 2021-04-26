#include "ciphers.hpp"

#include <algorithm>

wstring alberti_disk::encode(
        wstring const& message,
        wstring const& outer_disk,
        wstring inner_disk,
        int spin_step
) {
    if (outer_disk.size() != inner_disk.size()) {
        throw DisksDontMatch();
    }

    wstring result(message.length(), 0);
    for (size_t i {0}; i < message.length(); i += 1) {
        auto symbol_position {find(outer_disk.begin(), outer_disk.end(), message[i])};
        if (symbol_position == outer_disk.end()) {
            result[i] = message[i];
        } else {
            result[i] = inner_disk[symbol_position - outer_disk.begin()];
        }

        if (iswupper(message[i])) {
            if (spin_step < 0) {
                rotate(
                    inner_disk.rbegin(),
                    inner_disk.rbegin() + (-spin_step % inner_disk.length()),
                    inner_disk.rend()
                );
            } else if (spin_step > 0){
                rotate(
                    inner_disk.begin(),
                    inner_disk.begin() + (spin_step % inner_disk.length()),
                    inner_disk.end()
                );
            }
        }
    }
    return result;
}

wstring alberti_disk::decode(
        wstring const& code,
        wstring const& outer_disk,
        wstring inner_disk,
        int spin_step
) {
    if (outer_disk.size() != inner_disk.size()) {
        throw DisksDontMatch();
    }

    wstring result(code.length(), 0);
    for (size_t i {0}; i < code.length(); i += 1) {
        auto symbol_position {find(inner_disk.begin(), inner_disk.end(), code[i])};
        if (symbol_position == outer_disk.end()) {
            result[i] = code[i];
        } else {
            result[i] = outer_disk[symbol_position - inner_disk.begin()];
        }

        if (iswupper(result[i])) {
            if (spin_step < 0) {
                rotate(
                    inner_disk.rbegin(),
                    inner_disk.rbegin() + (-spin_step % inner_disk.length()),
                    inner_disk.rend()
                );
            } else if (spin_step > 0){
                rotate(
                    inner_disk.begin(),
                    inner_disk.begin() + (spin_step % inner_disk.length()),
                    inner_disk.end()
                );
            }
        }
    }
    return result;
}
