#include "hash.h"

unsigned char* SSHA(const unsigned char* msg, size_t length) {
    unsigned char A, B, C, D, E; //Initial Seed Value
    A = 56;
    B = 99;
    C = 102;
    D = 67;
    E = 76;

    for (int i = 0; i < length; i++) {
        for (int round = 0; round < 8; round++) {
            unsigned char g = (B & C) | (C & D);

            //every new value is calculated from the old values
            unsigned char newA = E;
            unsigned char newB = A;
            unsigned char newC = (A >> 2) + E;
            unsigned char newD = (A >> 2) ^ (B >> 1);
            unsigned char newE = (B >> 1) + g + msg[i];

            A = newA;
            B = newB;
            C = newC;
            D = newD;
            E = newE;
        }
      
    }
    unsigned char* digest = (unsigned char*)malloc(DIGEST_SIZE * sizeof(unsigned char));
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;
    return digest;
}

void SSHA2(const unsigned char* data, size_t len, unsigned char digest[SSHA2_DIGEST_LEN])
{
    unsigned char A = 56, B = 99, C = 102, D = 67, E = 76;
    size_t i;

    if (digest == NULL) {
        return;
    }
    if (data == NULL) {
        len = 0;
    }

    for (i = 0; i < len; i++) {
        /* Intermediate values, all computed from the OLD state */
        unsigned char a_shr2 = (unsigned char)(A >> 2);
        unsigned char b_shr1 = (unsigned char)(B >> 1);
        unsigned char choose = (unsigned char)((B & C) | (C & D));

        unsigned char newA = E;
        unsigned char newB = A;
        unsigned char newC = (unsigned char)(a_shr2 + E);
        unsigned char newD = (unsigned char)(a_shr2 ^ b_shr1);
        unsigned char newE = (unsigned char)(b_shr1 + choose + data[i]);

        A = newA;
        B = newB;
        C = newC;
        D = newD;
        E = newE;
    }

    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;
}

int digest_equal(struct Digest digest1, struct Digest digest2) {
    return ((digest1.hash0 == digest2.hash0) &&
        (digest1.hash1 == digest2.hash1) &&
        (digest1.hash2 == digest2.hash2) &&
        (digest1.hash3 == digest2.hash3) &&
        (digest1.hash4 == digest2.hash4));
    
}

void printDigest(struct Digest digest) {
    printf("%d %d %d %d %d\n", digest.hash0, digest.hash1, digest.hash2, digest.hash3, digest.hash4);
}