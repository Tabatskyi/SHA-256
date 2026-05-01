#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "sha256.h"

#define NUM_THREADS 8
#define PREFIX_SIZE 20
#define TARGET_ZEROS_BYTES 4

const char* target_message = "give my friend 2 bitcoins for a pizza";

volatile int found = 0;
uint8_t winning_prefix[PREFIX_SIZE];
uint8_t winning_hash[32];

typedef struct {
    uint8_t thread_id;
} thread_args;

void* search_worker(void* arg) {
    thread_args* targs = (thread_args*)arg;
    uint64_t nonce = (uint64_t)targs->thread_id << 56; 

    uint8_t prefix[PREFIX_SIZE] = {0};
    uint8_t hash[32];
    size_t msg_len = strlen(target_message);
    
    uint8_t full_data[128];
    memcpy(full_data + PREFIX_SIZE, target_message, msg_len);

    sha256_ctx ctx;

    while (!found) {
        memcpy(prefix, &nonce, sizeof(nonce));
        memcpy(full_data, prefix, PREFIX_SIZE);

        sha256_init(&ctx);
        sha256_update(&ctx, full_data, PREFIX_SIZE + msg_len);
        sha256_final(&ctx, hash);

        if (hash[0] == 0x00 && hash[1] == 0x00 && hash[2] == 0x00 && hash[3] == 0x00) {
            if (!found) {
                found = 1;
                memcpy(winning_prefix, prefix, PREFIX_SIZE);
                memcpy(winning_hash, hash, 32);
            }
            break;
        }
        nonce++;
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_args args[NUM_THREADS];

    printf("Starting prefix search with %d threads...\n", NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].thread_id = i;
        pthread_create(&threads[i], NULL, search_worker, &args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Match found!\n");
    printf("Prefix (Hex): ");
    for (int i = 0; i < PREFIX_SIZE; i++) {
        printf("%02x", winning_prefix[i]);
    }
    printf("\n");

    printf("Hash:         ");
    for (int i = 0; i < 32; i++) {
        printf("%02x", winning_hash[i]);
    }
    printf("\n");

    return 0;
}