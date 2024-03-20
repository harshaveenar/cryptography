#include <stdio.h>
#include <string.h>

// Function to decrypt the ciphertext
void decrypt(char *ciphertext) {
    char substitution[] = "etaoinshrdlcumwfgypbvkjxqz"; // Most frequent English letters
    int i, j;

    for (i = 0; i < strlen(ciphertext); i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            for (j = 0; j < 26; j++) {
                if (substitution[j] == ciphertext[i]) {
                    ciphertext[i] = 'a' + j;
                    break;
                }
            }
        }
    }
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 (88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";

    printf("Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext);

    printf("Decrypted message: %s\n", ciphertext);

    return 0;
}

