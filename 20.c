#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8 // Block size in bytes

// Dummy encryption function (replace with actual implementation)
void encrypt_block(char *plaintext_block, char *key, char *ciphertext_block) {
    strcpy(ciphertext_block, plaintext_block); // Dummy encryption, just copying plaintext to ciphertext
}

// Dummy decryption function (replace with actual implementation)
void decrypt_block(char *ciphertext_block, char *key, char *plaintext_block) {
    strcpy(plaintext_block, ciphertext_block); // Dummy decryption, just copying ciphertext to plaintext
}

// ECB Encryption
void ecb_encrypt(char *plaintext, char *key, char *ciphertext, int length) {
    int num_blocks = length / BLOCK_SIZE;
    for (int i = 0; i < num_blocks; i++) {
        encrypt_block(&plaintext[i * BLOCK_SIZE], key, &ciphertext[i * BLOCK_SIZE]);
    }
}

// ECB Decryption
void ecb_decrypt(char *ciphertext, char *key, char *plaintext, int length) {
    int num_blocks = length / BLOCK_SIZE;
    for (int i = 0; i < num_blocks; i++) {
        decrypt_block(&ciphertext[i * BLOCK_SIZE], key, &plaintext[i * BLOCK_SIZE]);
    }
}

// CBC Encryption
void cbc_encrypt(char *plaintext, char *key, char *ciphertext, int length, char *iv) {
    char *prev_block = iv; // Initialization vector for the first block
    int num_blocks = length / BLOCK_SIZE;
    for (int i = 0; i < num_blocks; i++) {
        char temp_block[BLOCK_SIZE];
        // XOR the plaintext with the previous ciphertext block
        for (int j = 0; j < BLOCK_SIZE; j++) {
            temp_block[j] = plaintext[i * BLOCK_SIZE + j] ^ prev_block[j];
        }
        // Encrypt the result and store it in the ciphertext
        encrypt_block(temp_block, key, &ciphertext[i * BLOCK_SIZE]);
        // Update the previous ciphertext block for the next iteration
        prev_block = &ciphertext[i * BLOCK_SIZE];
    }
}

// CBC Decryption
void cbc_decrypt(char *ciphertext, char *key, char *plaintext, int length, char *iv) {
    char *prev_block = iv; // Initialization vector for the first block
    int num_blocks = length / BLOCK_SIZE;
    for (int i = 0; i < num_blocks; i++) {
        char temp_block[BLOCK_SIZE];
        // Decrypt the current ciphertext block
        decrypt_block(&ciphertext[i * BLOCK_SIZE], key, temp_block);
        // XOR the decrypted block with the previous ciphertext block
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i * BLOCK_SIZE + j] = temp_block[j] ^ prev_block[j];
        }
        // Update the previous ciphertext block for the next iteration
        prev_block = &ciphertext[i * BLOCK_SIZE];
    }
}

int main() {
    char key[] = "secretK1"; // Encryption key
    char iv[] = "initvect";  // Initialization vector for CBC mode

    char plaintext[] = "Hello! This is a test message for ECB and CBC modes.";
    int length = strlen(plaintext);

    // Allocate memory for ciphertext
    char *ciphertext_ecb = (char *)malloc(length);
    char *ciphertext_cbc = (char *)malloc(length);

    // Allocate memory for decrypted plaintext
    char *decrypted_ecb = (char *)malloc(length);
    char *decrypted_cbc = (char *)malloc(length);

    // Perform ECB encryption and decryption
    ecb_encrypt(plaintext, key, ciphertext_ecb, length);
    ecb_decrypt(ciphertext_ecb, key, decrypted_ecb, length);

    // Perform CBC encryption and decryption
    cbc_encrypt(plaintext, key, ciphertext_cbc, length, iv);
    cbc_decrypt(ciphertext_cbc, key, decrypted_cbc, length, iv);

    // Output results
    printf("Original Plaintext: %s\n", plaintext);
    printf("ECB Encrypted: %s\n", ciphertext_ecb);
    printf("ECB Decrypted: %s\n", decrypted_ecb);
    printf("CBC Encrypted: %s\n", ciphertext_cbc);
    printf("CBC Decrypted: %s\n", decrypted_cbc);

    // Free dynamically allocated memory
    free(ciphertext_ecb);
    free(ciphertext_cbc);
    free(decrypted_ecb);
    free(decrypted_cbc);

    return 0;
}

