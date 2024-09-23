#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2

int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}

int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void inverse_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(matrix);
    int mod_inv = mod_inverse(det, 26);
    
    if (mod_inv == -1) {
        printf("Inverse does not exist.\n");
        return;
    }

    inverse[0][0] = (matrix[1][1] * mod_inv) % 26;
    inverse[0][1] = (-matrix[0][1] * mod_inv + 26) % 26;
    inverse[1][0] = (-matrix[1][0] * mod_inv + 26) % 26;
    inverse[1][1] = (matrix[0][0] * mod_inv) % 26;
}

void encrypt(int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext, char *ciphertext) {
    int pt_len = strlen(plaintext);
    for (int i = 0; i < pt_len; i += MATRIX_SIZE) {
        int block[MATRIX_SIZE] = {0, 0};
        
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (i + j < pt_len) {
                block[j] = plaintext[i + j] - 'A';
            }
        }
        
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[i / MATRIX_SIZE * MATRIX_SIZE + j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                ciphertext[i / MATRIX_SIZE * MATRIX_SIZE + j] += key[j][k] * block[k];
            }
            ciphertext[i / MATRIX_SIZE * MATRIX_SIZE + j] = (ciphertext[i / MATRIX_SIZE * MATRIX_SIZE + j] % 26) + 'A';
        }
    }
    ciphertext[pt_len] = '\0';
}

void decrypt(int key[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext, char *plaintext) {
    int inv_key[MATRIX_SIZE][MATRIX_SIZE];
    inverse_matrix(key, inv_key);
    
    int ct_len = strlen(ciphertext);
    for (int i = 0; i < ct_len; i += MATRIX_SIZE) {
        int block[MATRIX_SIZE] = {0, 0};

        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (i + j < ct_len) {
                block[j] = ciphertext[i + j] - 'A';
            }
        }

        for (int j = 0; j < MATRIX_SIZE; j++) {
            plaintext[i / MATRIX_SIZE * MATRIX_SIZE + j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                plaintext[i / MATRIX_SIZE * MATRIX_SIZE + j] += inv_key[j][k] * block[k];
            }
            plaintext[i / MATRIX_SIZE * MATRIX_SIZE + j] = (plaintext[i / MATRIX_SIZE * MATRIX_SIZE + j] % 26) + 'A';
        }
    }
    plaintext[ct_len] = '\0';
}

int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = {{6, 24}, {1, 13}};
    char plaintext[] = "HILL";
    char ciphertext[100];
    char decrypted[100];

    encrypt(key, plaintext, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt(key, ciphertext, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}

