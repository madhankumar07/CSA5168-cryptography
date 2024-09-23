#include <stdio.h>
#include <stdlib.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int isValidA(int a) {
    if (gcd(a, 26) == 1)
        return 1;
    else
        return 0;
}
char affineEncryptChar(int a, int b, char p) {
    if (p >= 'A' && p <= 'Z') {  
        return ((a * (p - 'A') + b) % 26) + 'A';
    } else if (p >= 'a' && p <= 'z') {  
        return ((a * (p - 'a') + b) % 26) + 'a';
    } else {
        return p;  
    }
}
char affineDecryptChar(int a, int b, char C) {
    int a_inv = 0;
    int flag = 0;
    for (int i = 0; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            a_inv = i;
            flag = 1;
            break;
        }
    }
    if (!flag) {
        printf("Multiplicative inverse for a=%d doesn't exist, decryption not possible.\n", a);
        return C;
    }
    if (C >= 'A' && C <= 'Z') {  
        return ((a_inv * ((C - 'A' - b + 26)) % 26) + 'A');
    } else if (C >= 'a' && C <= 'z') { 
        return ((a_inv * ((C - 'a' - b + 26)) % 26) + 'a');
    } else {
        return C;  
    }
}
void affineEncrypt(int a, int b, char* plaintext, char* ciphertext) {
    int i = 0;
    while (plaintext[i] != '\0') {
        ciphertext[i] = affineEncryptChar(a, b, plaintext[i]);
        i++;
    }
    ciphertext[i] = '\0';
}
void affineDecrypt(int a, int b, char* ciphertext, char* plaintext) {
    int i = 0;
    while (ciphertext[i] != '\0') {
        plaintext[i] = affineDecryptChar(a, b, ciphertext[i]);
        i++;
    }
    plaintext[i] = '\0';
}
int main() {
    int a, b;
    char plaintext[100], ciphertext[100], decryptedtext[100];
    printf("Enter the value of a (must be coprime with 26): ");
    scanf("%d", &a);
    if (!isValidA(a)) {
        printf("Invalid value for 'a'. It must be coprime with 26.\n");
        return 1;
    }
    printf("Enter the value of b (0 <= b <= 25): ");
    scanf("%d", &b);
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    affineEncrypt(a, b, plaintext, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    affineDecrypt(a, b, ciphertext, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);
    return 0;
}

