#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MATRIX_SIZE 2 
void encrypt(int keyMatrix[MATRIX_SIZE][MATRIX_SIZE], char *plaintext, char *ciphertext);
void decrypt(int keyMatrix[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext, char *plaintext);
void matrixInverse(int keyMatrix[MATRIX_SIZE][MATRIX_SIZE], int inverseMatrix[MATRIX_SIZE][MATRIX_SIZE]);
int mod(int a, int b);
void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]);

int main() {
    int keyMatrix[MATRIX_SIZE][MATRIX_SIZE] = {{6, 24}, {1, 15}}; 
    char plaintext[100], ciphertext[100], decryptedText[100];
    strcpy(plaintext, "HELP");
    encrypt(keyMatrix, plaintext, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    decrypt(keyMatrix, ciphertext, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);
    return 0;
}
void encrypt(int keyMatrix[MATRIX_SIZE][MATRIX_SIZE], char *plaintext, char *ciphertext) {
    int i, j;
    int textMatrix[MATRIX_SIZE][1];
    int cipherMatrix[MATRIX_SIZE][1];
    for (i = 0; i < MATRIX_SIZE; i++) {
        textMatrix[i][0] = plaintext[i] - 'A';
    }
    for (i = 0; i < MATRIX_SIZE; i++) {
        cipherMatrix[i][0] = 0;
        for (j = 0; j < MATRIX_SIZE; j++) {
            cipherMatrix[i][0] += keyMatrix[i][j] * textMatrix[j][0];
        }
        cipherMatrix[i][0] = mod(cipherMatrix[i][0], 26);
    }
    for (i = 0; i < MATRIX_SIZE; i++) {
        ciphertext[i] = cipherMatrix[i][0] + 'A';
    }
    ciphertext[MATRIX_SIZE] = '\0';
}
void decrypt(int keyMatrix[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext, char *plaintext) {
    int i, j;
    int textMatrix[MATRIX_SIZE][1];
    int cipherMatrix[MATRIX_SIZE][1];
    int inverseMatrix[MATRIX_SIZE][MATRIX_SIZE];
    matrixInverse(keyMatrix, inverseMatrix);
    for (i = 0; i < MATRIX_SIZE; i++) {
        cipherMatrix[i][0] = ciphertext[i] - 'A';
    }
    for (i = 0; i < MATRIX_SIZE; i++) {
        textMatrix[i][0] = 0;
        for (j = 0; j < MATRIX_SIZE; j++) {
            textMatrix[i][0] += inverseMatrix[i][j] * cipherMatrix[j][0];
        }
        textMatrix[i][0] = mod(textMatrix[i][0], 26);
    }
    for (i = 0; i < MATRIX_SIZE; i++) {
        plaintext[i] = textMatrix[i][0] + 'A';
    }
    plaintext[MATRIX_SIZE] = '\0';
}
int mod(int a, int b) {
    return ((a % b) + b) % b;
}
void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
void matrixInverse(int keyMatrix[MATRIX_SIZE][MATRIX_SIZE], int inverseMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int determinant = mod(keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0], 26);
    int adjointMatrix[MATRIX_SIZE][MATRIX_SIZE] = {{keyMatrix[1][1], -keyMatrix[0][1]}, {-keyMatrix[1][0], keyMatrix[0][0]}};
    int invDeterminant = mod(1, determinant); 
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            inverseMatrix[i][j] = mod(adjointMatrix[i][j] * invDeterminant, 26);
        }
    }
}

