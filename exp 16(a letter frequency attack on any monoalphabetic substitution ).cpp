#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char *ENGLISH_FREQ = "etaoinshrdlcumwfgypbvkjxqz";
void countFrequency(const char *ciphertext, int *frequency) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (ch >= 'a' && ch <= 'z') {
            frequency[ch - 'a']++;
        }
    }
}
void sortFrequency(int *frequency, char *sortedLetters) {
    for (int i = 0; i < 26; i++) {
        sortedLetters[i] = 'a' + i;
    }

    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 26; j++) {
            if (frequency[i] < frequency[j]) {            
                int temp = frequency[i];
                frequency[i] = frequency[j];
                frequency[j] = temp;
                char tempCh = sortedLetters[i];
                sortedLetters[i] = sortedLetters[j];
                sortedLetters[j] = tempCh;
            }
        }
    }
}
void generatePlaintexts(const char *ciphertext, char *sortedLetters, int topN) {
    for (int attempt = 0; attempt < topN; attempt++) {
        char mapping[26];
        for (int i = 0; i < 26; i++) {
            mapping[sortedLetters[i] - 'a'] = ENGLISH_FREQ[(i + attempt) % 26];
        }
        printf("Possible Plaintext #%d: ", attempt + 1);
        for (int i = 0; ciphertext[i] != '\0'; i++) {
            char ch = ciphertext[i];
            if (ch >= 'a' && ch <= 'z') {
                printf("%c", mapping[ch - 'a']);
            } else {
                printf("%c", ch); 
            }
        }
        printf("\n");
    }
}
int main() {
    char ciphertext[1000];
    int frequency[26] = {0};  
    char sortedLetters[26];   
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    countFrequency(ciphertext, frequency);
    sortFrequency(frequency, sortedLetters);
    int topN;
    printf("How many top possible plaintexts do you want? ");
    scanf("%d", &topN);
    generatePlaintexts(ciphertext, sortedLetters, topN);
    return 0;
}

