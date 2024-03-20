#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void calculateLetterFrequencies(char *text, int *frequency) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            frequency[tolower(text[i]) - 'a']++;
        }
    }
}

int findLikelyKey(int *frequency) {
    int maxFrequency = 0;
    int likelyKey = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > maxFrequency) {
            maxFrequency = frequency[i];
            likelyKey = i;
        }
    }

    return (likelyKey + 4) % ALPHABET_SIZE;
}

void decryptSubstitutionCipher(char *ciphertext, char *plaintext, char *key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            plaintext[i] = key[ciphertext[i] - 'a'];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

void letterFrequencyAttack(char *ciphertext, int topPlaintexts) {
    int frequency[ALPHABET_SIZE] = {0};
    int likelyKey = 0;
    char plaintext[strlen(ciphertext) + 1];
    char key[ALPHABET_SIZE + 1];

    calculateLetterFrequencies(ciphertext, frequency);
    likelyKey = findLikelyKey(frequency);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[(likelyKey + i) % ALPHABET_SIZE] = 'a' + i;
    }
    key[ALPHABET_SIZE] = '\0';

    printf("Top %d possible plaintexts:\n", topPlaintexts);
    for (int i = 0; i < topPlaintexts; i++) {
        decryptSubstitutionCipher(ciphertext, plaintext, key);
        printf("%d. %s\n", i + 1, plaintext);
        char temp = key[0];
        for (int j = 0; j < ALPHABET_SIZE - 1; j++) {
            key[j] = key[j + 1];
        }
        key[ALPHABET_SIZE - 1] = temp;
    }
}

int main() {
    char ciphertext[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";
    int topPlaintexts = 10;

    letterFrequencyAttack(ciphertext, topPlaintexts);

    return 0;
}

