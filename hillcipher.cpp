#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Include for toupper function

#define MOD 26

// Function to calculate the modular inverse of a number
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if (((a % m) * (x % m)) % m == 1) {
            return x;
        }
    }
    return -1; // Modular inverse does not exist
}

// Function to encrypt a message using a 2x2 matrix key
void hillEncrypt(char message[], int key[2][2]) {
    int len = strlen(message);
    int pairs = len / 2;

    if (len % 2 != 0) {
        printf("Message length must be even.\n");
        return;
    }

    for (int i = 0; i < pairs; i++) {
        int m1 = toupper(message[2*i]) - 'A';
        int m2 = toupper(message[2*i + 1]) - 'A';

        int result1 = (key[0][0] * m1 + key[0][1] * m2) % MOD;
        int result2 = (key[1][0] * m1 + key[1][1] * m2) % MOD;

        printf("%c%c", result1 + 'A', result2 + 'A');
    }
    printf("\n");
}

int main() {
    int key[2][2] = {{2, 4}, {5, 3}}; // Example key matrix
    char message[] = "HELLOWORLD"; // Example message

    printf("Original message: %s\n", message);
    printf("Encrypted message: ");
    hillEncrypt(message, key);

    return 0;
}

