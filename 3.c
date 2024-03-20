#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char table[SIZE][SIZE];

// Function to generate the key matrix
void generateKeyMatrix(char key[]) {
    int i, j, k, flag = 0, *dict;

    dict = (int *)calloc(26, sizeof(int));

    for(i = 0; i < strlen(key); i++) {
        if(key[i] != 'j')
            dict[key[i] - 'a'] = 2;
    }

    dict['j' - 'a'] = 1;

    i = 0;
    j = 0;

    for(k = 0; k < strlen(key); k++) {
        if(dict[key[k] - 'a'] == 2) {
            dict[key[k] - 'a'] -= 1;
            table[i][j++] = key[k];
            if(j == SIZE) {
                j = 0;
                i++;
            }
        }
    }

    for(k = 0; k < 26; k++) {
        if(dict[k] == 0) {
            table[i][j++] = (char)(k + 'a');
            dict[k] = -1;
            if(j == SIZE) {
                j = 0;
                i++;
            }
        }
    }
}

// Function to get the position of a character in the key matrix
void getPosition(char ch, int *row, int *col) {
    int i, j;

    if(ch == 'j')
        ch = 'i';

    for(i = 0; i < SIZE; i++) {
        for(j = 0; j < SIZE; j++) {
            if(table[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt the plaintext
char* encrypt(char *message) {
    int length = strlen(message);
    int i, row1, row2, col1, col2;
    char *cipher = (char *)malloc(sizeof(char) * (length * 2 + 1));
    char a, b;

    for(i = 0; i < length; i += 2) {
        a = message[i];
        b = message[i + 1];

        if(a == b)
            b = 'x';

        getPosition(a, &row1, &col1);
        getPosition(b, &row2, &col2);

        if(row1 == row2) {
            cipher[i * 2] = table[row1][(col1 + 1) % SIZE];
            cipher[i * 2 + 1] = table[row2][(col2 + 1) % SIZE];
        }
        else if(col1 == col2) {
            cipher[i * 2] = table[(row1 + 1) % SIZE][col1];
            cipher[i * 2 + 1] = table[(row2 + 1) % SIZE][col2];
        }
        else {
            cipher[i * 2] = table[row1][col2];
            cipher[i * 2 + 1] = table[row2][col1];
        }
    }
    cipher[length * 2] = '\0';
    return cipher;
}

int main() {
    char key[26], message[1000], *cipher;
    
    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0; // Remove newline if present

    generateKeyMatrix(key);

    printf("Enter message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; // Remove newline if present

    cipher = encrypt(message);
    printf("Encrypted message: %s\n", cipher);

    free(cipher);
    return 0;
}

