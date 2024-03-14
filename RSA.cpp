#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
long long int mod_exp(long long int base, unsigned int exp, int mod) {
    long long int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

void generate_keys(int p, int q, int *public_key, int *private_key, int *n) {
    int phi_n = (p - 1) * (q - 1);
    *n = p * q;
    int e = 2;
    while (e < phi_n) {
        if (gcd(e, phi_n) == 1)
            break;
        e++;
    }

    *public_key = e;

    int k = 2;
    while (1) {
        if (((k * phi_n) + 1) % e == 0)
            break;
        k++;
    }

    *private_key = ((k * phi_n) + 1) / e;
}

// Function to encrypt the message
long long int encrypt(int message, int public_key, int n) {
    return mod_exp(message, public_key, n);
}

// Function to decrypt the message
long long int decrypt(long long int encrypted_message, int private_key, int n) {
    return mod_exp(encrypted_message, private_key, n);
}

int main() {
    int p, q, public_key, private_key, n;
    printf("Enter two prime numbers (p and q): ");
    scanf("%d %d", &p, &q);

    generate_keys(p, q, &public_key, &private_key, &n);
    printf("Public Key: %d\nPrivate Key: %d\nn: %d\n", public_key, private_key, n);

    int message;
    printf("Enter an integer message to encrypt: ");
    scanf("%d", &message);

    long long int encrypted_message = encrypt(message, public_key, n);
    printf("Encrypted message: %lld\n", encrypted_message);

    long long int decrypted_message = decrypt(encrypted_message, private_key, n);
    printf("Decrypted message: %lld\n", decrypted_message);

    return 0;
}
