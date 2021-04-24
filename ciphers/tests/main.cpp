#include <gtest/gtest.h>
#include <windows.h>

#include "../ciphers.hpp"

int main(int argc, char** argv) {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
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
