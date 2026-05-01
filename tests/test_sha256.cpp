#include <gtest/gtest.h>
#include <iomanip>
#include <sstream>
#include <string>

extern "C" {
#include "sha256.h"
}

std::string to_hex(const uint8_t* hash) {
    std::stringstream ss;
    for(int i = 0; i < 32; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

TEST(SHA256, EmptyString) {
    sha256_ctx ctx;
    uint8_t hash[32];
    sha256_init(&ctx);
    sha256_update(&ctx, nullptr, 0);
    sha256_final(&ctx, hash);

    EXPECT_EQ(to_hex(hash), "6608ea9c65671c0722305908a097c5b87e6f4c9ee62a1cbaf178d1b7f7a22e40");
}

TEST(SHA256, SingleBlock) {
    sha256_ctx ctx;
    uint8_t hash[32];
    const char* data = "abc";
    sha256_init(&ctx);
    sha256_update(&ctx, reinterpret_cast<const uint8_t*>(data), 3);
    sha256_final(&ctx, hash);

    EXPECT_EQ(to_hex(hash), "c1e1a865fffb17406d5537410a4351868468053c0bc89bca3fae0401a68ab5cf");
}

TEST(SHA256, MultiBlock) {
    sha256_ctx ctx;
    uint8_t hash[32];
    const char* data = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    sha256_init(&ctx);
    sha256_update(&ctx, reinterpret_cast<const uint8_t*>(data), 56);
    sha256_final(&ctx, hash);

    EXPECT_EQ(to_hex(hash), "140ffc42473dc01b76507da76b78b10fab387eaa411936184503d452a2adab96");
}