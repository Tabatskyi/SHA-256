#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "sha256.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <path_to_certificate.der>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    sha256_ctx ctx;
    sha256_init(&ctx);

    uint8_t buffer[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        sha256_update(&ctx, buffer, bytes_read);
    }

    fclose(file);

    uint8_t hash[32];
    sha256_final(&ctx, hash);

    printf("Fingerprint:\n");
    for (int i = 0; i < 32; i++) {
        printf("%02X", hash[i]);
        if (i < 31) {
            printf(":");
        }
    }
    printf("\n");

    return 0;
}