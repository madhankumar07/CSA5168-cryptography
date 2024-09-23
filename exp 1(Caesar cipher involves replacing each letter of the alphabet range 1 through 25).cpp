#include <stdio.h>
#include <ctype.h>
void encrypt(char text[], int k) {
    char ch;
    for (int i = 0; text[i] != '\0'; i++) {
        ch = text[i];
        if (islower(ch)) {
            ch = (ch - 'a' + k) % 26 + 'a';
        }
        else if (isupper(ch)) {
            ch = (ch - 'A' + k) % 26 + 'A';
        }
        text[i] = ch; 
    }
}
int main() {
    char text[100];
    int k;
    printf("Enter a string to encrypt: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter shift value (1-25): ");
    scanf("%d", &k);
    if (k < 1 || k > 25) {
        printf("Invalid shift value! It must be between 1 and 25.\n");
        return 1;
    }
    encrypt(text, k);
    printf("Encrypted text: %s\n", text);
    return 0;
}

