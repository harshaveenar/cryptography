#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to generate the cipher sequence based on the keyword
void generateCipherSequence(char *keyword, char *cipherSequence) {
    int used[ALPHABET_SIZE] = {0};
    int keywordLen = strlen(keyword);
    int i, j;

    // Copy the keyword to the cipher sequence
    strcpy(cipherSequence, keyword);

    // Mark characters of the keyword as used
    for (i = 0; i < keywordLen; i++) {
        if (isalpha(keyword[i])) {
            if (isupper(keyword[i])) {
                used[keyword[i] - 'A'] = 1;
            } else if (islower(keyword[i])) {
                used[keyword[i] - 'a'] = 1;
            }
        }
    }

    // Fill the remaining unused characters in the cipher sequence
    j = keywordLen;
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if (!used[i]) {
            cipherSequence[j++] = 'A' + i;
        }
    }
    cipherSequence[j] = '\0';
}

// Function to encrypt the plaintext using the generated cipher sequence
void encrypt(char *plaintext, char *cipherSequence) {
    int i;

    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            if (isupper(plaintext[i])) {
                plaintext[i] = cipherSequence[plaintext[i] - 'A'];
            } else if (islower(plaintext[i])) {
                plaintext[i] = tolower(cipherSequence[plaintext[i] - 'a']);
            }
        }
    }
}

int main() {
    char keyword[] = "CIPHER";
    char cipherSequence[ALPHABET_SIZE + 1];
    char plaintext[1000];

    // Generate the cipher sequence
    generateCipherSequence(keyword, cipherSequence);
    printf("Cipher sequence: %s\n", cipherSequence);

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    // Encrypt the plaintext
    encrypt(plaintext, cipherSequence);
    printf("Encrypted message: %s\n", plaintext);

    return 0;
}

