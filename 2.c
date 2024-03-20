#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

char* createCipherAlphabet(char key[]) {
    char* cipherAlphabet = (char*)malloc(ALPHABET_SIZE * sizeof(char));
    int i, j;
    int keyLength = strlen(key);

    for (i = 0; i < ALPHABET_SIZE; ++i) {
        cipherAlphabet[i] = ' ';
    }

    for (i = 0; i < keyLength; ++i) {
        if (!isalpha(key[i])) {
            printf("Invalid key. Key should contain only alphabets.\n");
            exit(1);
        }
        key[i] = toupper(key[i]);
        if (cipherAlphabet[key[i] - 'A'] == ' ') {
            cipherAlphabet[key[i] - 'A'] = key[i];
        } else {
            printf("Invalid key. Key should contain unique alphabets.\n");
            exit(1);
        }
    }

    for (i = 0, j = 0; i < ALPHABET_SIZE; ++i) {
        if (cipherAlphabet[i] == ' ') {
            char ch = 'A' + j;
            while (strchr(key, ch) != NULL) {
                ++ch;
            }
            cipherAlphabet[i] = ch;
            ++j;
        }
    }

    return cipherAlphabet;
}

void monoalphabeticSubstitution(char* cipherAlphabet, char message[]) {
    int i;

    for (i = 0; message[i] != '\0'; ++i) {
        if (isalpha(message[i])) {
            if (islower(message[i])) {
                message[i] = tolower(cipherAlphabet[message[i] - 'a']);
            } else {
                message[i] = cipherAlphabet[message[i] - 'A'];
            }
        }
    }

    printf("Encrypted message: %s\n", message);
}

int main() {
    char key[ALPHABET_SIZE + 1];
    char* cipherAlphabet;
    char message[100];

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    if (strlen(key) != ALPHABET_SIZE) {
        printf("Invalid key length. Key length should be %d.\n", ALPHABET_SIZE);
        return 1;
    }

    cipherAlphabet = createCipherAlphabet(key);

    printf("Enter message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    monoalphabeticSubstitution(cipherAlphabet, message);

    free(cipherAlphabet);

    return 0;
}

