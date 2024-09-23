#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
void generateCipherAlphabet(const char* keyword, char* cipherAlphabet);
void encryptDecrypt(const char* text, const char* cipherAlphabet, char* result, int mode);
void toUpperCase(char* str);
int charToIndex(char c);
char indexToChar(int index);
int main() {
    const char* keyword = "CIPHER";
    char cipherAlphabet[ALPHABET_SIZE + 1] = {0};
    char plaintext[100], ciphertext[100], decryptedtext[100];
    generateCipherAlphabet(keyword, cipherAlphabet);
    printf("Cipher Alphabet: %s\n", cipherAlphabet);
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0;  
    encryptDecrypt(plaintext, cipherAlphabet, ciphertext, 1);
    printf("Ciphertext: %s\n", ciphertext);
    encryptDecrypt(ciphertext, cipherAlphabet, decryptedtext, 0);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
void generateCipherAlphabet(const char* keyword, char* cipherAlphabet) {
    int used[ALPHABET_SIZE] = {0};
    int index = 0;
    for (int i = 0; keyword[i]; i++) {
        char c = toupper(keyword[i]);
        if (isalpha(c) && !used[charToIndex(c)]) {
            cipherAlphabet[index++] = c;
            used[charToIndex(c)] = 1;
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (!used[i]) {
            cipherAlphabet[index++] = indexToChar(i);
        }
    }
    cipherAlphabet[index] = '\0';
}
void encryptDecrypt(const char* text, const char* cipherAlphabet, char* result, int mode) {
    const char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char mapping[ALPHABET_SIZE];
    char reverseMapping[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        mapping[i] = cipherAlphabet[i];
        reverseMapping[charToIndex(cipherAlphabet[i])] = alphabet[i];
    }
    for (int i = 0; text[i]; i++) {
        char c = toupper(text[i]);
        if (isalpha(c)) {
            int index = charToIndex(c);
            result[i] = mode ? mapping[index] : reverseMapping[index];
        } else {
            result[i] = text[i];  
        }
    }
    result[strlen(text)] = '\0';
}
int charToIndex(char c) {
    return toupper(c) - 'A';
}
char indexToChar(int index) {
    return 'A' + index;
}
void toUpperCase(char* str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

