#include <stdio.h>
#include "rc4.h"

int main() {
    int i;
    uint8_t key[5] = {0x01, 0x02, 0x03, 0x04, 0x05};
    uint8_t input[10] = {0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9};
    uint8_t encrypt[10];
    uint8_t decrypt[10];

    rc4_state_t *state = rc4_create(key, 5);

    printf("rc4_state Example\n\n");

    printf("orignal data: ");
    for (i = 0; i < 10; i++) {
        printf("%02x ", input[i]);
    }
    printf("\n");

    rc4_crypt(state, input, encrypt, 10);
    rc4_destroy(state);

    printf("encrypt data: ");
    for (i = 0; i < 10; i++) {
        printf("%02x ", encrypt[i]);
    }
    printf("\n");

    state = rc4_create(key, 5);
    rc4_crypt(state, encrypt, decrypt, 10);
    rc4_destroy(state);

    printf("decrypt data: ");
    for (i = 0; i < 10; i++) {
        printf("%02x ", decrypt[i]);
    }
    printf("\n");

    return 0;
}