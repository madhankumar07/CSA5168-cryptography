#include <stdio.h>
#include <stdint.h>
const int PC1[56] = { 
    57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
};
const int PC2[48] = { 
    14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};
const int SHIFTS[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
uint32_t leftCircularShift(uint32_t n, int shift) {
    return ((n << shift) | (n >> (28 - shift))) & 0x0FFFFFFF;
}
void generateKeys(uint64_t key, uint64_t subKeys[16]) {
    uint64_t permutedKey = 0;
    uint32_t C = 0, D = 0;
    int i, j;
    for (i = 0; i < 28; i++) {
        C |= ((key >> (64 - PC1[i])) & 1) << (27 - i);
        D |= ((key >> (64 - PC1[i + 28])) & 1) << (27 - i);
    }
    for (i = 0; i < 16; i++) {
        C = leftCircularShift(C, SHIFTS[i]);
        D = leftCircularShift(D, SHIFTS[i]);
        uint64_t combined = ((uint64_t)C << 28) | D;
        subKeys[i] = 0;
        for (j = 0; j < 48; j++) {
            subKeys[i] |= ((combined >> (56 - PC2[j])) & 1) << (47 - j);
        }
    }
}
uint64_t initialPermutation(uint64_t block) {
    return block;
}

uint64_t finalPermutation(uint64_t block) {
    return block;
}

uint32_t fFunction(uint32_t R, uint64_t K) {
    return R ^ (K & 0xFFFFFFFF);
}
uint64_t desDecrypt(uint64_t ciphertext, uint64_t key) {
    uint64_t subKeys[16], permutedBlock, L, R, temp;
    int i;
    generateKeys(key, subKeys);
    permutedBlock = initialPermutation(ciphertext);
    L = (permutedBlock >> 32) & 0xFFFFFFFF;
    R = permutedBlock & 0xFFFFFFFF;
    for (i = 15; i >= 0; i--) {
        temp = L;
        L = R;
        R = temp ^ fFunction(R, subKeys[i]);
    }
    uint64_t decryptedBlock = ((uint64_t)R << 32) | L;
    return finalPermutation(decryptedBlock);
}
int main() {
    uint64_t ciphertext = 0x123456789ABCDEF0; 
    uint64_t key = 0x133457799BBCDFF1;        
    uint64_t plaintext = desDecrypt(ciphertext, key);
    printf("Decrypted plaintext: %llx\n", plaintext);
    return 0;
}

