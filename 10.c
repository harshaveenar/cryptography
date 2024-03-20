#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void generatePlayfairMatrix(char matrix[SIZE][SIZE]) {
    char key[] = "MFHIJ KUNO PQZVW XYELARGDSTBC";
    int i, j, k = 0;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            matrix[i][j] = key[k++];
            if (matrix[i][j] == 'J') 
                matrix[i][j] = 'I';
        }
    }
}
void normalizePlaintext(char *plaintext) {
    int i, j;
    for (i = 0; plaintext[i] != '\0'; i++) {
        plaintext[i] = toupper(plaintext[i]);
        if (plaintext[i] == 'J')
            plaintext[i] = 'I';
    }
}
void encryptPlayfair(char matrix[SIZE][SIZE], char *plaintext, char *ciphertext) {
    normalizePlaintext(plaintext);

    int len = strlen(plaintext);
    int i, j;
    int row1, row2, col1, col2;

    for (i = 0; i < len; i += 2) {
        char a = plaintext[i];
        char b = (plaintext[i + 1] == '\0') ? 'X' : plaintext[i + 1]; 

        for (j = 0; j < SIZE * SIZE; j++) {
            if (matrix[j / SIZE][j % SIZE] == a) {
                row1 = j / SIZE;
                col1 = j % SIZE;
            }
            if (matrix[j / SIZE][j % SIZE] == b) {
                row2 = j / SIZE;
                col2 = j % SIZE;
            }
        }

        if (row1 == row2) {
            ciphertext[i] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[i] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}

int main() {
    char matrix[SIZE][SIZE];
    generatePlayfairMatrix(matrix);

    char plaintext[] = "Must see you over Cadogan West. Coming at once.";
    char ciphertext[100];

    encryptPlayfair(matrix, plaintext, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

