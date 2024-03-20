#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to decrypt ciphertext using additive cipher with a given key
void decryptAdditiveCipher(char *ciphertext, int key, char *plaintext) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - base - key + 26) % 26) + base;
        } else {
            plaintext[i] = ciphertext[i]; // Copy non-alphabetic characters as is
        }
    }
    plaintext[i] = '\0';
}

// Function to calculate letter frequencies in a string
void calculateLetterFrequencies(char *text, int *frequency) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            frequency[tolower(text[i]) - 'a']++;
        }
    }
}

// Function to find the most likely key based on letter frequencies
int findLikelyKey(int *frequency) {
    int maxFrequency = 0;
    int likelyKey = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > maxFrequency) {
            maxFrequency = frequency[i];
            likelyKey = i;
        }
    }

    // Assuming 'e' is the most frequent letter in English, its index in the alphabet is 4 (zero-based)
    return (likelyKey + 22) % ALPHABET_SIZE; // Shift to align 'e' frequency with the correct key
}

// Function to perform a letter frequency attack on an additive cipher
void letterFrequencyAttack(char *ciphertext, int topPlaintexts) {
    int frequency[ALPHABET_SIZE] = {0};
    int likelyKey = 0;
    char plaintext[strlen(ciphertext) + 1];

    // Calculate letter frequencies in the ciphertext
    calculateLetterFrequencies(ciphertext, frequency);

    // Find the most likely key based on letter frequencies
    likelyKey = findLikelyKey(frequency);

    printf("Most likely key: %d\n", likelyKey);

    printf("Top %d possible plaintexts:\n", topPlaintexts);
    for (int i = 0; i < topPlaintexts; i++) {
        decryptAdditiveCipher(ciphertext, (likelyKey + i) % ALPHABET_SIZE, plaintext);
        printf("%d. %s\n", i + 1, plaintext);
    }
}

int main() {
    char ciphertext[] = "Uifsf jt b tfdsfu, boe ju xjmm cf b tupq mbof bddpvoubcmf boe uibu't uifsf.";
    int topPlaintexts = 10;

    letterFrequencyAttack(ciphertext, topPlaintexts);

    return 0;
}

