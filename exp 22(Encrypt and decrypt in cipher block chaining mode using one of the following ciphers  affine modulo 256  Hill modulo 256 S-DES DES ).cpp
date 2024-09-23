#include <stdio.h>
#include <stdint.h>

void generateKeys(uint8_t key, uint8_t *K1, uint8_t *K2) {
    *K1 = (key & 0xF0) >> 4;
    *K2 = (key & 0x0F);
}

uint8_t sdesEncrypt(uint8_t plaintext, uint8_t key) {
    return plaintext ^ key;
}

uint8_t sdesDecrypt(uint8_t ciphertext, uint8_t key) {
    return ciphertext ^ key;
}

void cbcEncrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t iv, uint8_t K1, uint8_t K2, int length) {
    uint8_t previousBlock = iv;
    for (int i = 0; i < length; i++) {
        uint8_t block = plaintext[i] ^ previousBlock;
        ciphertext[i] = sdesEncrypt(block, K1);
        previousBlock = ciphertext[i];
    }
}

void cbcDecrypt(uint8_t *ciphertext, uint8_t *plaintext, uint8_t iv, uint8_t K1, uint8_t K2, int length) {
    uint8_t previousBlock = iv;
    for (int i = 0; i < length; i++) {
        uint8_t block = sdesDecrypt(ciphertext[i], K1);
        plaintext[i] = block ^ previousBlock;
        previousBlock = ciphertext[i];
    }
}

int main() {
    uint8_t iv = 0xAA;
    uint8_t plaintext[] = {0x01, 0x23};
    uint8_t key = 0x7D;
    uint8_t K1, K2;
    uint8_t ciphertext[2];
    uint8_t decryptedtext[2];

    generateKeys(key, &K1, &K2);

    cbcEncrypt(plaintext, ciphertext, iv, K1, K2, 2);

    cbcDecrypt(ciphertext, decryptedtext, iv, K1, K2, 2);

    printf("Plaintext: ");
    for (int i = 0; i < 2; i++) {
        printf("%02x ", plaintext[i]);
    }
    printf("\nCiphertext: ");
    for (int i = 0; i < 2; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\nDecrypted text: ");
    for (int i = 0; i < 2; i++) {
        printf("%02x ", decryptedtext[i]);
    }
    printf("\n");

    return 0;
}

