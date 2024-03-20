#include <stdio.h>

// Function to encrypt using the Affine Caesar Cipher
char encryptAffineCaesar(char p, int a, int b) {
    if (isalpha(p)) {
        char base = isupper(p) ? 'A' : 'a';
        return ((a * (p - base) + b) % 26) + base;
    }
    return p; // Return unchanged if not a letter
}

int main() {
    char plaintext;
    int a, b;

    printf("Enter plaintext character: ");
    scanf("%c", &plaintext);

    printf("Enter value of a: ");
    scanf("%d", &a);

    printf("Enter value of b: ");
    scanf("%d", &b);

    char ciphertext = encryptAffineCaesar(plaintext, a, b);
    printf("Ciphertext: %c\n", ciphertext);

    return 0;
}

