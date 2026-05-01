#include <stdio.h>
#include <stdint.h>
#include "sha256.h"

int main(void) {
    for (int i = 0; i < 5; i++) {
        printf("Hello from C23! Iteration %d\n", i);
    }

    return 0;
}
