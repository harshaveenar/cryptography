#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000

void encryptPolyalphabetic(char *plaintext, char *key, char *ciphertext) {
    int keyLen = strlen(key);
    int textLen = strlen(plaintext);

    for (int i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            int shift = tolower(key[i % keyLen]) - 'a';
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (base + (plaintext[i] - base + shift) % 26);
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[textLen] = '\0';
}

int main() {
    char plaintext[MAX_TEXT_LENGTH];
    char key[MAX_TEXT_LENGTH];
    char ciphertext[MAX_TEXT_LENGTH];

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);

    encryptPolyalphabetic(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

