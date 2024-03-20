#include <stdio.h>
#include <ctype.h>

void caesarCipher(char message[], int key) {
    char ch;
    int i;

    for(i = 0; message[i] != '\0'; ++i) {
        ch = message[i];

        if(isalpha(ch)) {
            if(isupper(ch)) {
                ch = ((ch - 'A') + key) % 26 + 'A';
            }
            else {
                ch = ((ch - 'a') + key) % 26 + 'a';
            }
        }
        message[i] = ch;
    }

    printf("Encrypted message: %s\n", message);
}

int main() {
    char message[100];
    int key, i;

    printf("Enter message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter key (1-25): ");
    scanf("%d", &key);

    if(key < 1 || key > 25) {
        printf("Invalid key. Key should be between 1 and 25.\n");
        return 1;
    }

    caesarCipher(message, key);

    return 0;
}

