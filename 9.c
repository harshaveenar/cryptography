#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
void generateKeyMatrix(char key[], char matrix[SIZE][SIZE]) {
    int i, j, k, len;
    int filled[26] = {0};

    len = strlen(key);
    k = 0;
    for (i = 0; i < len; i++) {
        if (key[i] >= 'A' && key[i] <= 'Z') {
            key[i] = tolower(key[i]);
        }
        if (key[i] == 'j') {
            key[i] = 'i'; 
        }

        if (!filled[key[i] - 'a']) {
            matrix[k / SIZE][k % SIZE] = key[i];
            filled[key[i] - 'a'] = 1;
            k++;
        }
    }
    for (i = 0; i < 26; i++) {
        if (!filled[i] && i != ('j' - 'a')) {
            matrix[k / SIZE][k % SIZE] = 'a' + i;
            k++;
        }
    }
}
void decryptPlayfair(char ciphertext[], char key[]) {
    char matrix[SIZE][SIZE];
    int i, j;
    char a, b;
    int row1, row2, col1, col2;
    generateKeyMatrix(key, matrix);
    for (i = 0; ciphertext[i] != '\0'; i += 2) {
        a = ciphertext[i];
        b = ciphertext[i + 1];

        // Find positions of letters in the matrix
        for (j = 0; j < SIZE; j++) {
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
            printf("%c%c", matrix[row1][(col1 + SIZE - 1) % SIZE], matrix[row2][(col2 + SIZE - 1) % SIZE]);
        } else if (col1 == col2) {
            printf("%c%c", matrix[(row1 + SIZE - 1) % SIZE][col1], matrix[(row2 + SIZE - 1) % SIZE][col2]);
        } else {
            printf("%c%c", matrix[row1][col2], matrix[row2][col1]);
        }
    }
}

int main() {
    char key[] = "playfair";
    char ciphertext[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";

    printf("Decrypted message: ");
    decryptPlayfair(ciphertext, key);
    printf("\n");

    return 0;
}

