#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void createMatrix(char *key, char matrix[SIZE][SIZE]) {
    int used[26] = {0};
    int k = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        char c = toupper(key[i]);
        if (c == 'J') c = 'I'; 
        if (c >= 'A' && c <= 'Z' && !used[c - 'A']) {
            matrix[k / SIZE][k % SIZE] = c;
            used[c - 'A'] = 1;
            k++;
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue; 
        if (!used[c - 'A']) {
            matrix[k / SIZE][k % SIZE] = c;
            k++;
        }
    }
}
void searchMatrix(char matrix[SIZE][SIZE], char a, char b, int *row1, int *col1, int *row2, int *col2) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == a) {
                *row1 = i;
                *col1 = j;
            }
            if (matrix[i][j] == b) {
                *row2 = i;
                *col2 = j;
            }
        }
    }
}
void decryptPlayfair(char *message, char *key, char *output) {
    char matrix[SIZE][SIZE];
    createMatrix(key, matrix);  
    int len = strlen(message);
    int index = 0;
    for (int i = 0; i < len; i += 2) {
        char a = toupper(message[i]);
        char b = toupper(message[i + 1]); 
        if (a == 'J') a = 'I';
        if (b == 'J') b = 'I';
        int row1, col1, row2, col2;
        searchMatrix(matrix, a, b, &row1, &col1, &row2, &col2);
        if (row1 == row2) {
            output[index++] = matrix[row1][(col1 - 1 + SIZE) % SIZE];
            output[index++] = matrix[row2][(col2 - 1 + SIZE) % SIZE];
        } else if (col1 == col2) {
            output[index++] = matrix[(row1 - 1 + SIZE) % SIZE][col1];
            output[index++] = matrix[(row2 - 1 + SIZE) % SIZE][col2];
        } else {
            output[index++] = matrix[row1][col2];
            output[index++] = matrix[row2][col1];
        }
    }
    output[index] = '\0';
}
int main() {
    char key[] = "YOURKEYWORD"; 
    char message[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";
    char output[1000];
    decryptPlayfair(message, key, output);
    printf("Decrypted Message: %s\n", output);
    return 0;
}

