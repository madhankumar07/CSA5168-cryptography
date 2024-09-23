#include <stdio.h>
#include <string.h>
char decryptAffine(char ch) {
    int a_inv = 9;  
    int b = 15;     
    if (ch >= 'A' && ch <= 'Z') {
        int y = ch - 'A'; 
        int decrypted = (a_inv * (y - b + 26)) % 26;  
        return (decrypted + 'A');  
    }
    return ch; 
}
void decryptMessage(const char* ciphertext, char* plaintext) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        plaintext[i] = decryptAffine(ciphertext[i]);
    }
    plaintext[i] = '\0';  
}
int main() {
    char ciphertext[] = "BU...";  
    char plaintext[100];          
    decryptMessage(ciphertext, plaintext);
    printf("Decrypted message: %s\n", plaintext);
    return 0;
}

