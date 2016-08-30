#ifndef __RC4_H
#define __RC4_H

#include <stdint.h>

typedef struct RC4Chiper RC4Chiper_t;
typedef void (*RC4CryptFunc)(RC4Chiper_t *, uint8_t *, uint8_t *, int);

struct RC4Chiper {
    RC4CryptFunc crypt;
    uint8_t s[256];
    int i;
    int j;
};

/**
 * init a rc4 chiper
 */
void RC4Chiper_init(RC4Chiper_t *chiper, uint8_t *key, int keysize);

/**
 * create and init a rc4 chiper
 * RC4Chiper_t memory will create with molloc, use RC4Chiper_init if you have custom molloc/free
 */
RC4Chiper_t *RC4Chiper_create(uint8_t *key, int keysize);

/**
 * destroy(free) a rc4 chiper
 */
void RC4Chiper_destroy(RC4Chiper_t *chiper);

#endif
