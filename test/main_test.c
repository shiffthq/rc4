#include <stdlib.h>

#include "minunit.h"
#include "rc4.h"

// https://tools.ietf.org/html/rfc6229#section-2
MU_TEST(rc4_state_40bit) {
    int i;
    uint8_t input[] = {0x00};
    uint8_t output[1];

    uint8_t key[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    uint8_t expect[] = {
        0xb2, 0x39, 0x63, 0x05, 0xf0, 0x3d,0xc0, 0x27, 0xcc, 0xc3, 0x52, 0x4a, 0x0a, 0x11, 0x18, 0xa8,
        0x69, 0x82, 0x94, 0x4f, 0x18, 0xfc,0x82, 0xd5, 0x89, 0xc4, 0x03, 0xa4, 0x7a, 0x0d, 0x09, 0x19
    };

    rc4_state_t *state = rc4_create(key, 5);

    for (i = 0; i < 16; i++) {
        rc4_crypt(state, input, output, 1);
        mu_check(output[0] == expect[i]);
    }
    rc4_destroy(state);
}

MU_TEST(rc4_encrypt_decrypt) {
    int i;
    uint8_t key[5] = {0x01, 0x02, 0x03, 0x04, 0x05};
    uint8_t input[10] = {0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9};
    uint8_t encrypt[10];
    uint8_t decrypt[10];

    rc4_state_t *state = NULL;

    state = rc4_create(key, 5);
    rc4_crypt(state, input, encrypt, 10);
    rc4_destroy(state);

    state = rc4_create(key, 5);
    rc4_crypt(state, encrypt, decrypt, 10);
    rc4_destroy(state);

    for (i = 0; i < 10; i++) {
        mu_check(input[i] == decrypt[i]);
    }
}

int main(int argc, char **argv) {
    MU_RUN_TEST(rc4_state_40bit);

    MU_RUN_TEST(rc4_encrypt_decrypt);

    MU_REPORT();
    return 0;
}
