#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void fillMatrix(char matrix[SIZE][SIZE], char *key) {
    int used[26] = {0};
    int k = 0;
    for (int i = 0; key[i]; i++) {
        if (key[i] == 'J') key[i] = 'I'; 
        if (!used[key[i] - 'A']) {
            used[key[i] - 'A'] = 1;
            matrix[k / SIZE][k % SIZE] = key[i];
            k++;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!used[ch - 'A']) {
            matrix[k / SIZE][k % SIZE] = ch;
            k++;
        }
    }
}

void preprocessText(char *text, char *processed) {
    int j = 0;
    for (int i = 0; text[i]; i++) {
        if (text[i] == 'J') text[i] = 'I';
        if (isalpha(text[i])) {
            processed[j++] = toupper(text[i]);
        }
    }
    processed[j] = '\0';
    for (int i = 0; processed[i + 1]; i += 2) {
        if (processed[i] == processed[i + 1]) {
            for (int j = strlen(processed); j > i + 1; j--) {
                processed[j] = processed[j - 1];
            }
            processed[i + 1] = 'X';
        }
    }
    if (strlen(processed) % 2 != 0) {
        strcat(processed, "X");
    }
}
void encryptDigraph(char *digraph, char matrix[SIZE][SIZE], char *encrypted) {
    int row1, col1, row2, col2;
    for (int i = 0; i < 2; i++) {
        for (int r = 0; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                if (matrix[r][c] == digraph[i]) {
                    if (i == 0) {
                        row1 = r; col1 = c;
                    } else {
                        row2 = r; col2 = c;
                    }
                }
            }
        }
    }
    
    if (row1 == row2) {
        encrypted[0] = matrix[row1][(col1 + 1) % SIZE];
        encrypted[1] = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        encrypted[0] = matrix[(row1 + 1) % SIZE][col1];
        encrypted[1] = matrix[(row2 + 1) % SIZE][col2];
    } else {
        encrypted[0] = matrix[row1][col2];
        encrypted[1] = matrix[row2][col1];
    }
}

int main() {
    char key[] = "MFHIKUNOPQZVWXYYELARGDSTBC";
    char matrix[SIZE][SIZE];
    char text[] = "Must see you over Cadogan West. Coming at once";
    char processed[100];
    char encrypted[3];
    
    fillMatrix(matrix, key);
    
    preprocessText(text, processed);
    printf("Playfair Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    } 
    printf("Encrypted Text: ");
    for (int i = 0; processed[i]; i += 2) {
        encryptDigraph(&processed[i], matrix, encrypted);
        printf("%c%c", encrypted[0], encrypted[1]);
    }
    printf("\n");
    return 0;
}

