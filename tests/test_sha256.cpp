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

    EXPECT_EQ(to_hex(hash), "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
}

TEST(SHA256, SingleBlock) {
    sha256_ctx ctx;
    uint8_t hash[32];
    const char* data = "abc";
    sha256_init(&ctx);
    sha256_update(&ctx, reinterpret_cast<const uint8_t*>(data), 3);
    sha256_final(&ctx, hash);

    EXPECT_EQ(to_hex(hash), "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
}

TEST(SHA256, MultiBlock) {
    sha256_ctx ctx;
    uint8_t hash[32];
    const char* data = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    sha256_init(&ctx);
    sha256_update(&ctx, reinterpret_cast<const uint8_t*>(data), 56);
    sha256_final(&ctx, hash);

    EXPECT_EQ(to_hex(hash), "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
}