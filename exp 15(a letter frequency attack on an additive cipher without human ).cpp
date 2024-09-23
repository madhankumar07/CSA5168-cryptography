#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#define ALPHABET_SIZE 26
void calculateFrequency(const char *text, int *frequency) {
    memset(frequency, 0, ALPHABET_SIZE * sizeof(int));
    while (*text) {
        if (isalpha(*text)) {
            frequency[toupper(*text) - 'A']++;
        }
        text++;
    }
}
void decrypt(const char *ciphertext, int shift, char *plaintext) {
    while (*ciphertext) {
        if (isalpha(*ciphertext)) {
            char base = islower(*ciphertext) ? 'a' : 'A';
            *plaintext = ((toupper(*ciphertext) - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
        } else {
            *plaintext = *ciphertext;
        }
        ciphertext++;
        plaintext++;
    }
    *plaintext = '\0';
}
void rankPlaintexts(const char *ciphertext, int topN) {
    int frequency[ALPHABET_SIZE];
    char plaintext[256];
    int rank[ALPHABET_SIZE];
    calculateFrequency(ciphertext, frequency);
    printf("Possible plaintexts (top %d):\n", topN);
    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        decrypt(ciphertext, shift, plaintext);
        int decryptedFrequency[ALPHABET_SIZE];
        calculateFrequency(plaintext, decryptedFrequency);
        int similarity = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            similarity += frequency[i] - decryptedFrequency[i];
        }
        rank[shift] = similarity;
    }
    for (int i = 0; i < topN; i++) {
        int minIndex = 0;
        for (int j = 1; j < ALPHABET_SIZE; j++) {
            if (rank[j] < rank[minIndex]) {
                minIndex = j;
            }
        }
        decrypt(ciphertext, minIndex, plaintext);
        printf("Shift %d: %s\n", minIndex, plaintext);
        rank[minIndex] = INT_MAX;
    }
}
int main() {
    char ciphertext[256];
    int topN;
    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    printf("Enter number of top possible plaintexts to display: ");
    scanf("%d", &topN);
    rankPlaintexts(ciphertext, topN);
    return 0;
}

