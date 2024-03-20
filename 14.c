#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
void encryptVigenereOTP(char *plaintext, int *key, char *ciphertext) {
    int keyLength = strlen(plaintext);
    int i;

    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((plaintext[i] - base + key[i]) % 26) + base;
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[i] = '\0';
}
void decryptVigenereOTP(char *ciphertext, int *key, char *plaintext) {
    int keyLength = strlen(ciphertext);
    int i;

    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - base - key[i] + 26) % 26) + base;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char plaintext[] = "sendmoremoney";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    char ciphertext[sizeof(plaintext)];
    char decrypted[sizeof(plaintext)];
    encryptVigenereOTP(plaintext, key, ciphertext);
    printf("Encrypted ciphertext: %s\n", ciphertext);
    decryptVigenereOTP(ciphertext, key, decrypted);
    printf("Decrypted plaintext: %s\n", decrypted);

    return 0;
}

