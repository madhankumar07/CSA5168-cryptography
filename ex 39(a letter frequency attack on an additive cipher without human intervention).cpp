#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_LENGTH 1000
#define TOP_N 10

void calculate_frequency(const char *ciphertext, int *frequency) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        char ch = ciphertext[i];
        if (ch >= 'a' && ch <= 'z') {
            frequency[ch - 'a']++;
        } else if (ch >= 'A' && ch <= 'Z') {
            frequency[ch - 'A']++;
        }
    }
}

void decrypt(const char *ciphertext, int shift, char *plaintext) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        char ch = ciphertext[i];
        if (ch >= 'a' && ch <= 'z') {
            plaintext[i] = (ch - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
        } else if (ch >= 'A' && ch <= 'Z') {
            plaintext[i] = (ch - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE + 'A';
        } else {
            plaintext[i] = ch;
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

void frequency_attack(const char *ciphertext) {
    int frequency[ALPHABET_SIZE] = {0};
    calculate_frequency(ciphertext, frequency);

    int shift_scores[ALPHABET_SIZE] = {0};
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        shift_scores[i] = frequency[(i + ('e' - 'a' + ALPHABET_SIZE)) % ALPHABET_SIZE];
    }

    char plaintext[MAX_TEXT_LENGTH];
    for (int i = 0; i < TOP_N; i++) {
        int max_index = 0;
        for (int j = 1; j < ALPHABET_SIZE; j++) {
            if (shift_scores[j] > shift_scores[max_index]) {
                max_index = j;
            }
        }
        
        decrypt(ciphertext, max_index, plaintext);
        printf("Possible plaintext with shift %d: %s\n", max_index, plaintext);

        shift_scores[max_index] = -1;
    }
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];

    printf("Enter the cipher text: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    frequency_attack(ciphertext);

    return 0;
}

