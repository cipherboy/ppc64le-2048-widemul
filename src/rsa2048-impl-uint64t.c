#include <stdint.h>
#include <stddef.h>
#include <assert.h>

#include "r2048i.h"
#include "r2048u64t.h"

void u64t_translate(_u64t *ret, r2048bn *parameter) {
    assert(parameter->length < (1 << 13));
    ret->length = parameter->length << 3;
    assert((ret->length & 64) == 0);

    for (size_t i_u64t = 0; i_u64t < (ret->length >> 6); i_u64t++) {
        ret->data[i_u64t] = 0;
        for (size_t o_r2048bn = 8; o_r2048bn > 0; o_r2048bn--) {
            ret->data[i_u64t] <<= 8;
            ret->data[i_u64t] |= parameter->data[(8*i_u64t) + o_r2048bn - 1];
        }
    }
}

void r2048bn_translate(r2048bn *ret, _u64t *parameter) {
    uint64_t data;
    ret->length = parameter->length >> 3;

    for (size_t i_u64t = 0; i_u64t < (ret->length >> 6); i_u64t++) {
        data = parameter->data[i_u64t];
        for (size_t i_r2048bn = (8*i_u64t); i_r2048bn < (8*(i_u64t+1) - 1); i_r2048bn++) {
            ret->data[i_r2048bn] = (uint8_t)(data & 0xFF);
            data >>= 8;
        }
    }
}

void r2048_modulus(r2048bn *ret_n, r2048bn *prime_p, r2048bn *prime_q) {
    _u64t N;
    _u64t P;
    _u64t Q;

    u64t_translate(&P, prime_p);
    u64t_translate(&Q, prime_q);

    u64t_modulus(&N, &P, &Q);

    r2048bn_translate(ret_n, &N);
}

void r2048_exponent(r2048bn *ret_decryption, r2048bn *mod_n, r2048bn *exp_e) {
    _u64t D;
    _u64t N;
    _u64t E;

    u64t_translate(&N, mod_n);
    u64t_translate(&E, exp_e);

    u64t_exponent(&D, &N, &E);

    r2048bn_translate(ret_decryption, &D);
}

void r2048_crypt(r2048bn *ret, r2048bn *message, r2048bn *mod_n, r2048bn *exponent) {
    _u64t RET;
    _u64t M;
    _u64t N;
    _u64t E;

    u64t_translate(&M, message);
    u64t_translate(&N, mod_n);
    u64t_translate(&E, exponent);

    u64t_crypt(&RET, &M, &N, &E);

    r2048bn_translate(ret, &RET);
}

void u64t_modulus(_u64t *ret_n, _u64t *prime_p, _u64t *prime_q) {}
void u64t_exponent(_u64t *ret_decryption, _u64t *mod_n, _u64t *exp_e) {}
void u64t_crypt(_u64t *ret, _u64t *message, _u64t *mod_n, _u64t *exponent) {}

