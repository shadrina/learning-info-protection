#ifndef LAB_2_AES_H
#define LAB_2_AES_H

#include <iostream>
#include <stdexcept>
#include <vector>

typedef uint8_t word[4];

class AESCipher {
private:
    static uint8_t cipher_key[];
    static uint8_t s_box[256];
    static uint8_t inv_s_box[256];
    static uint8_t R[];
    static int Nb;

    static void rot_word(word w);
    static void sub_word(word w);
    static uint8_t gmult(uint8_t a, uint8_t b);
    static uint8_t * Rcon(uint8_t i);
    static void coef_add(const word a, const word b, word d);
    static void add_round_key(uint8_t *state, const uint8_t *w, uint8_t r);
    static void sub_bytes(uint8_t *state);
    static void inv_sub_bytes(uint8_t *state);
    static void shift_rows(uint8_t *state);
    static void inv_shift_rows(uint8_t *state);
    static void coef_mult(uint8_t *a, uint8_t *b, uint8_t *d);
    static void mix_columns(uint8_t *state);
    static void inv_mix_columns(uint8_t *state);

    uint8_t *round_key;
    int Nk;
    int Nr;

    void expand_key();

public:
    AESCipher();

    void cipher(const uint8_t *in, uint8_t *out);
    void inv_cipher(const uint8_t *in, uint8_t *out);

    ~AESCipher();
};

#endif //LAB_2_AES_H
