#include <stdlib.h>
#include <assert.h>
#include "rc4.h"

static inline void swap(uint8_t *array, int i, int j) {
    uint8_t tmp;

    tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

static uint8_t RC4Chiper_generatekey(RC4Chiper_t *chiper) {
    chiper->i = (chiper->i + 1) & 0xff;
    chiper->j = (chiper->j + chiper->s[chiper->i]) & 0xff;

    swap(chiper->s, chiper->i, chiper->j);

    return chiper->s[(chiper->s[chiper->i] + chiper->s[chiper->j]) & 0xff];
}

static void RC4Chiper_crypt(RC4Chiper_t *chiper, uint8_t *input, uint8_t *output, int buflen) {
    int i;
    uint8_t key;

    for (i = 0; i < buflen; i++) {
        key = RC4Chiper_generatekey(chiper);
        output[i] = input[i] ^ key;
    }
}

void RC4Chiper_init(RC4Chiper_t *chiper, uint8_t *key, int keysize) {
    int i, j;

    assert(chiper);
    assert(key);

    chiper->i = 0;
    chiper->j = 0;
    chiper->crypt = RC4Chiper_crypt;

    for (i = 0; i < 256; i++) {
        chiper->s[i] = i;
    }

    for (i = j = 0; i < 256; i++) {
        j = (j + chiper->s[i] + key[i % keysize]) & 0xff;

        swap(chiper->s, i, j);
    }
}

RC4Chiper_t *RC4Chiper_create(uint8_t *key, int keysize) {
    RC4Chiper_t *chiper = NULL;

    chiper = malloc(sizeof(RC4Chiper_t));
    if (NULL == chiper) {
        return NULL;
    }

    RC4Chiper_init(chiper, key, keysize);

    return chiper;
}

void RC4Chiper_destroy(RC4Chiper_t *chiper) {
    free(chiper);
}
