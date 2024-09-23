#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
char matrix[SIZE][SIZE];
int mark[26] = {0}; 
void prepareMatrix(char key[]) {
    int len = strlen(key);
    int x = 0, y = 0;
    for (int i = 0; i < len; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I'; 

        if (!mark[ch - 'A']) {
            matrix[x][y++] = ch;
            mark[ch - 'A'] = 1;
            if (y == SIZE) {
                x++;
                y = 0;
            }
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; 

        if (!mark[ch - 'A']) {
            matrix[x][y++] = ch;
            mark[ch - 'A'] = 1;
            if (y == SIZE) {
                x++;
                y = 0;
            }
        }
    }
}
void printMatrix() {
    printf("Playfair Cipher Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}
int preparePlaintext(char plaintext[], char digraphs[][2]) {
    int len = strlen(plaintext);
    int count = 0;
    for (int i = 0; i < len; i++) {
        char ch1 = toupper(plaintext[i]);
        if (!isalpha(ch1)) continue;
        if (i < len - 1) {
            char ch2 = toupper(plaintext[i + 1]);
            if (!isalpha(ch2) || ch1 == ch2) {
                digraphs[count][0] = ch1;
                digraphs[count][1] = 'X'; 
            } else {
                digraphs[count][0] = ch1;
                digraphs[count][1] = ch2;
                i++;
            }
        } else {
            digraphs[count][0] = ch1;
            digraphs[count][1] = 'X';
        }
        count++;
    }
    return count; 
}
void findPosition(char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptPair(char *ch1, char *ch2) {
    int row1, col1, row2, col2;
    findPosition(*ch1, &row1, &col1);
    findPosition(*ch2, &row2, &col2);
    if (row1 == row2) {
        *ch1 = matrix[row1][(col1 + 1) % SIZE];
        *ch2 = matrix[row2][(col2 + 1) % SIZE];
    }
    else if (col1 == col2) {
        *ch1 = matrix[(row1 + 1) % SIZE][col1];
        *ch2 = matrix[(row2 + 1) % SIZE][col2];
    }
    else {
        *ch1 = matrix[row1][col2];
        *ch2 = matrix[row2][col1];
    }
}
void encrypt(char plaintext[]) {
    char digraphs[100][2]; 
    int digraphCount;
    digraphCount = preparePlaintext(plaintext, digraphs);
    printf("Ciphertext: ");
    for (int i = 0; i < digraphCount; i++) {
        encryptPair(&digraphs[i][0], &digraphs[i][1]);
        printf("%c%c ", digraphs[i][0], digraphs[i][1]);
    }
    printf("\n");
}
int main() {
    char key[100], plaintext[100];
    printf("Enter the keyword: ");
    scanf("%s", key);
    prepareMatrix(key);
    printMatrix();
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    encrypt(plaintext);

    return 0;
}

