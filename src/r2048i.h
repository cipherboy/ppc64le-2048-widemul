/*
 * This file implements a high-level interface for 2048-bit RSA
 * multiplication. Given pre-generated 1024-bit primes P and Q,
 * we can:
 *
 *      - Compute the modulus N,
 *      - Compute the decryption exponent D, assuming e=65535.
 *      - Compute the encryption or decryption of data.
 *
 * This header file represents a high-level interface that implementations
 * should adhere to. In particular, it does _not_ use pveclib in order to
 * avoid biasing against non-vectorized implementations.
 */

#pragma once

/*
 * r2048bn: big integer struct
 *
 * Large enough to hold a 4096-bit result. Smaller indices are less
 * significant than bigger indices.data[0] is thus the least significant byte,
 * data[length-1] is the most significant. This essentially guarantees that we
 * have enough overhead for scratch work.
 */
typedef struct {
    uint8_t data[512];
    uint16_t length;
} r2048bn;

/* Semantics:
 *
 *      - Caller allocates all data including return parameter.
 *      - Return parameters come first.
 *      - Always pass pointers.
 */

extern void r2048_modulus(r2048bn *ret_n, r2048bn *prime_p, r2048bn *prime_q);
extern void r2048_exponent(r2048bn *ret_decryption, r2048bn *mod_n, r2048bn *exp_e);
extern void r2048_crypt(r2048bn *ret, r2048bn *message, r2048bn *mod_n, r2048bn *exponent);
