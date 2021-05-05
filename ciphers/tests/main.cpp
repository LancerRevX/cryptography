#include <gtest/gtest.h>
#include <windows.h>

#include <iostream>

#include "../ciphers.hpp"

int main(int argc, char** argv) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::cout << iswupper(L'Ä') << std::endl;
    std::cout << iswupper(L'ä') << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(richelieu, key_too_long) {
    EXPECT_THROW(richelieu::encode(L"123456", {{3,2,1},{2,1},{1,2}}), richelieu::KeyLongerThanMessage);
}

TEST(richelieu, invalid_key_segment_sequence) {
    EXPECT_THROW(richelieu::encode(L"123456", {{4,2,1}}), richelieu::InvalidKeySegment);
    EXPECT_THROW(richelieu::encode(L"123456", {{1,1}}), richelieu::InvalidKeySegment);
    EXPECT_THROW(richelieu::encode(L"123456", {{3,1}}), richelieu::InvalidKeySegment);
    EXPECT_THROW(richelieu::encode(L"123456", {{3,2,1},{4,3,2}}), richelieu::InvalidKeySegment);
}

TEST(richelieu, encoding_examples) {
    EXPECT_EQ(richelieu::encode(L"криптография", {{3,2,1},{4,2,3,1},{1},{2,1},{2,1}}), L"иркгтопрфаяи");
    EXPECT_EQ(richelieu::encode(L"криптография", {{3,2,1}}), L"иркптография");
    EXPECT_EQ(richelieu::encode(L"криптография", {{2,1},{2,1},{2,1},{2,1},{2,1},{2,1}}), L"ркпиотргфаяи");
}

TEST(richelieu, decoding_examples) {
    EXPECT_EQ(richelieu::encode(L"иркгтопрфаяи", {{3,2,1},{4,2,3,1},{1},{2,1},{2,1}}), L"криптография");
    EXPECT_EQ(richelieu::encode(L"иркптография", {{3,2,1}}), L"криптография");
    EXPECT_EQ(richelieu::encode(L"ркпиотргфаяи", {{2,1},{2,1},{2,1},{2,1},{2,1},{2,1}}), L"криптография");
}

const vector<wstring> alphabets {
    L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя",
    L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ",
    L"abcdefghijklmnopqrstuvwxyz",
    L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
};

TEST(gronsveld, encoding) {
    EXPECT_EQ(
        gronsveld::encode(L"GRONSFELD", alphabets, {2,0,1,5}),
        L"IRPSUFFQF"
    );
}

TEST(gronsveld, decoding) {
    EXPECT_EQ(
        gronsveld::decode(L"IRPSUFFQF", alphabets, {2,0,1,5}),
        L"GRONSFELD"
    );
}

TEST(vigenere, encoding) {
    EXPECT_EQ(
        vigenere::encode(L"ATTACKATDAWN", alphabets[3], L"LEMON"),
        L"LXFOPVEFRNHR"
    );
}

TEST(vigenere, decoding) {
    EXPECT_EQ(
        vigenere::decode(L"LXFOPVEFRNHR", alphabets[3], L"LEMON"),
        L"ATTACKATDAWN"
    );
}

TEST(playfair, encoding_matrix) {
    EXPECT_EQ(
        playfair::get_encoding_matrix(
            {
                {L"A", L"B", L"C", L"D", L"E"},
                {L"F", L"G", L"H", L"IJ", L"K"},
                {L"L", L"M", L"N", L"O", L"P"},
                {L"Q", L"R", L"S", L"T", L"U"},
                {L"V", L"W", L"X", L"Y", L"Z"}
            },
            L"WHEATSON"
        ),
        vector<vector<wstring>>({
            {L"W", L"H", L"E", L"A", L"T"},
            {L"S", L"O", L"N", L"B", L"C"},
            {L"D", L"F", L"G", L"IJ", L"K"},
            {L"L", L"M", L"P", L"Q", L"R"},
            {L"U", L"V", L"X", L"Y", L"Z"}
        })
    );
    EXPECT_EQ(
        playfair::get_encoding_matrix(
            {
                {L"A", L"B", L"C", L"D", L"E"},
                {L"F", L"G", L"H", L"IJ", L"K"},
                {L"L", L"M", L"N", L"O", L"P"},
                {L"Q", L"R", L"S", L"T", L"U"},
                {L"V", L"W", L"X", L"Y", L"Z"}
            },
            L"PLAYFAIREXAMPLE"
            ),
        vector<vector<wstring>>({
            {L"P", L"L", L"A", L"Y", L"F"},
            {L"IJ", L"R", L"E", L"X", L"M"},
            {L"B", L"C", L"D", L"G", L"H"},
            {L"K", L"N", L"O", L"Q", L"S"},
            {L"T", L"U", L"V", L"W", L"Z"}
        })
    );
}

TEST(playfair, encoding) {
    EXPECT_EQ(
        playfair::encode(
            L"IDIOCYOFTENLOOKSLIKEINTELLIGENCE",
            {
                {L"A", L"B", L"C", L"D", L"E"},
                {L"F", L"G", L"H", L"IJ", L"K"},
                {L"L", L"M", L"N", L"O", L"P"},
                {L"Q", L"R", L"S", L"T", L"U"},
                {L"V", L"W", L"X", L"Y", L"Z"}
            },
            L"WHEATSON",
            L'X'
        ),
        L"KFFBBZFMWASPNVCFDUKDAGCEWPQDPNBSNE"
    );
    EXPECT_EQ(
        playfair::encode(
            L"HIDETHEGOLDINTHETREESTUMP",
            {
                {L"A", L"B", L"C", L"D", L"E"},
                {L"F", L"G", L"H", L"IJ", L"K"},
                {L"L", L"M", L"N", L"O", L"P"},
                {L"Q", L"R", L"S", L"T", L"U"},
                {L"V", L"W", L"X", L"Y", L"Z"}
            },
            L"PLAYFAIREXAMPLE",
            L'X'
            ),
        L"BMODZBXDNABEKUDMUIXMMOUVIF"
    );
}

TEST(playfair, decoding) {
    EXPECT_EQ(
        playfair::decode(
            L"KFFBBZFMWASPNVCFDUKDAGCEWPQDPNBSNE",
            {
                {L"A", L"B", L"C", L"D", L"E"},
                {L"F", L"G", L"H", L"IJ", L"K"},
                {L"L", L"M", L"N", L"O", L"P"},
                {L"Q", L"R", L"S", L"T", L"U"},
                {L"V", L"W", L"X", L"Y", L"Z"}
            },
            L"WHEATSON",
            L'X'
        ),
        L"IDIOCYOFTENLOXOKSLIKEINTELLIGENCEX"
    );
    EXPECT_EQ(
        playfair::decode(
            L"BMODZBXDNABEKUDMUIXMMOUVIF",
            {
                {L"A", L"B", L"C", L"D", L"E"},
                {L"F", L"G", L"H", L"IJ", L"K"},
                {L"L", L"M", L"N", L"O", L"P"},
                {L"Q", L"R", L"S", L"T", L"U"},
                {L"V", L"W", L"X", L"Y", L"Z"}
            },
            L"PLAYFAIREXAMPLE",
            L'X'
            ),
        L"HIDETHEGOLDINTHETREXESTUMP"
    );
}

TEST(hill, encoding) {
    EXPECT_EQ(
        hill::encode(
            L"ACT",
            alphabets[3],
            {
                {6, 24, 1},
                {13, 16, 10},
                {20, 17, 15}
            }
        ),
        L"POH"
    );

    EXPECT_EQ(
        hill::encode(
            L"CAT",
            alphabets[3],
            {
                {6, 24, 1},
                {13, 16, 10},
                {20, 17, 15}
            }
            ),
        L"FIN"
    );
}

TEST(hill, decoding) {
    EXPECT_EQ(
        hill::decode(
            L"POH",
            alphabets[3],
            {
                {6, 24, 1},
                {13, 16, 10},
                {20, 17, 15}
            }
            ),
        L"ACT"
    );

    EXPECT_EQ(
        hill::decode(
            L"FIN",
            alphabets[3],
            {
                {6, 24, 1},
                {13, 16, 10},
                {20, 17, 15}
            }
            ),
        L"CAT"
    );
}
