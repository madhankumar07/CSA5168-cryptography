#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define ALPHABET_SIZE 26
void createMapping(char *plainAlphabet, char *cipherAlphabet, char *mapping, char *reverseMapping) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        mapping[plainAlphabet[i] - 'A'] = cipherAlphabet[i];
        reverseMapping[cipherAlphabet[i] - 'A'] = plainAlphabet[i];
    }
}
void encrypt(char *plaintext, char *mapping, char *ciphertext) {
    while (*plaintext) {
        if (isalpha(*plaintext)) {
            if (isupper(*plaintext)) {
                *ciphertext = mapping[*plaintext - 'A'];
            } else {
                *ciphertext = tolower(mapping[toupper(*plaintext) - 'A']);
            }
            ciphertext++;
        } else {
            *ciphertext = *plaintext;
            ciphertext++;
        }
        plaintext++;
    }
    *ciphertext = '\0';
}
void decrypt(char *ciphertext, char *reverseMapping, char *plaintext) {
    while (*ciphertext) {
        if (isalpha(*ciphertext)) {
            if (isupper(*ciphertext)) {
                *plaintext = reverseMapping[*ciphertext - 'A'];
            } else {
                *plaintext = tolower(reverseMapping[toupper(*ciphertext) - 'A']);
            }
            plaintext++;
        } else {
            *plaintext = *ciphertext;
            plaintext++;
        }
        ciphertext++;
    }
    *plaintext = '\0';
}
int main() {
    char plainAlphabet[ALPHABET_SIZE + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char cipherAlphabet[ALPHABET_SIZE + 1] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    int counts[ALPHABET_SIZE] = {0};
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (cipherAlphabet[i] < 'A' || cipherAlphabet[i] > 'Z') {
            printf("Error: Cipher alphabet must be all uppercase letters.\n");
            return 1;
        }
        if (counts[cipherAlphabet[i] - 'A']++ > 0) {
            printf("Error: Cipher alphabet must contain unique letters.\n");
            return 1;
        }
    }
    char mapping[ALPHABET_SIZE];
    char reverseMapping[ALPHABET_SIZE];
    createMapping(plainAlphabet, cipherAlphabet, mapping, reverseMapping);
    char plaintext[256];
    char ciphertext[256];
    char decryptedText[256];
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    encrypt(plaintext, mapping, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    decrypt(ciphertext, reverseMapping, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);
    return 0;
}

