#pragma once

#include <stdint.h>

typedef struct {
    uint64_t data[64];

    // Length in bits
    uint16_t length;
} _u64t;

extern void u64t_translate(_u64t *ret, r2048bn *parameter);
extern void r2048bn_translate(r2048bn *ret, _u64t *parameter);

extern void u64t_modulus(_u64t *ret_n, _u64t *prime_p, _u64t *prime_q);
extern void u64t_exponent(_u64t *ret_decryption, _u64t *mod_n, _u64t *exp_e);
extern void u64t_crypt(_u64t *ret, _u64t *message, _u64t *mod_n, _u64t *exponent);
