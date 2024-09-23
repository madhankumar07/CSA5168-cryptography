#include <stdio.h>
#include <string.h>
#define BLOCK_SIZE 16
void xor_blocks(unsigned char *output, unsigned char *block1, unsigned char *block2) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

void encrypt_block(unsigned char *output, unsigned char *input) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ 0xFF;
    }
}

void ecb_encrypt(unsigned char *ciphertext, unsigned char *plaintext, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        encrypt_block(&ciphertext[i], &plaintext[i]);
    }
}

void cbc_encrypt(unsigned char *ciphertext, unsigned char *plaintext, int length, unsigned char *iv) {
    unsigned char buffer[BLOCK_SIZE];
    xor_blocks(buffer, plaintext, iv);
    encrypt_block(ciphertext, buffer);

    for (int i = BLOCK_SIZE; i < length; i += BLOCK_SIZE) {
        xor_blocks(buffer, &plaintext[i], &ciphertext[i - BLOCK_SIZE]);
        encrypt_block(&ciphertext[i], buffer);
    }
}

void print_hex(unsigned char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main() {
    const char *message = "HelloWorld123456HelloWorld123456";
    unsigned char plaintext[BLOCK_SIZE * 2 + 1];
    strcpy((char *)plaintext, message);

    unsigned char ciphertext_ecb[BLOCK_SIZE * 2];
    unsigned char ciphertext_cbc[BLOCK_SIZE * 2];
    unsigned char iv[BLOCK_SIZE] = "InitializationV";

    ecb_encrypt(ciphertext_ecb, plaintext, sizeof(plaintext) - 1);
    printf("ECB Ciphertext: ");
    print_hex(ciphertext_ecb, sizeof(ciphertext_ecb));

    cbc_encrypt(ciphertext_cbc, plaintext, sizeof(plaintext) - 1, iv);
    printf("CBC Ciphertext: ");
    print_hex(ciphertext_cbc, sizeof(ciphertext_cbc));

    return 0;
}

