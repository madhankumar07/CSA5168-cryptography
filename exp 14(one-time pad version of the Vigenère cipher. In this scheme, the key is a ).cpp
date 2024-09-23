#include <stdio.h>
#include <string.h>
#define ALPHABET_SIZE 26
void encrypt(char *plaintext, int *key, int key_length, char *ciphertext) {
    int i;
    int text_length = strlen(plaintext);
    for (i = 0; i < text_length; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            int shift = key[i % key_length];
            ciphertext[i] = 'a' + (plaintext[i] - 'a' + shift) % ALPHABET_SIZE;
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[text_length] = '\0';
}
void decrypt(char *ciphertext, int *key, int key_length, char *plaintext) {
    int i;
    int text_length = strlen(ciphertext);
    for (i = 0; i < text_length; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            int shift = key[i % key_length];
            plaintext[i] = 'a' + (ciphertext[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[text_length] = '\0';
}
void find_key(char *ciphertext, char *plaintext, int *key, int key_length) {
    int i;
    int text_length = strlen(ciphertext);

    for (i = 0; i < text_length; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            int shift = (ciphertext[i] - plaintext[i] + ALPHABET_SIZE) % ALPHABET_SIZE;
            key[i % key_length] = shift;
        }
    }
}
int main() {
    char plaintext[] = "send more money";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int key_length = sizeof(key) / sizeof(key[0]);
    char ciphertext[strlen(plaintext) + 1];
    char decryptedtext[strlen(plaintext) + 1];
    encrypt(plaintext, key, key_length, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    decrypt(ciphertext, key, key_length, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);
    char desired_plaintext[] = "cash not needed";
    int found_key[key_length];
    find_key(ciphertext, desired_plaintext, found_key, key_length);
    printf("Key for desired plaintext:\n");
    for (int i = 0; i < key_length; i++) {
        printf("%d ", found_key[i]);
    }
    printf("\n");

    return 0;
}

