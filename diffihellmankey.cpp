#include <stdio.h>
#include <math.h>
long long int power(long long int a, long long int b, long long int P) {
    if (b == 1)
        return a;

    else
        return (((long long int)pow(a, b)) % P);
}

long long int compute_key(long long int G, long long int a, long long int P) {
    return power(G, a, P);
}
int main() {
    long long int P, G, a, b;
    printf("Enter the value of P (a prime number): ");
    scanf("%lld", &P);
    printf("Enter the value of G (a primitive root of %lld): ", P);
    scanf("%lld", &G);
    printf("Enter Alice's private key (a): ");
    scanf("%lld", &a);
    printf("Enter Bob's private key (b): ");
    scanf("%lld", &b);
    long long int A = compute_key(G, a, P);
    printf("Alice's public key (A): %lld\n", A);
    long long int B = compute_key(G, b, P);
    printf("Bob's public key (B): %lld\n", B);
    long long int secret_key_Alice = compute_key(B, a, P);
    long long int secret_key_Bob = compute_key(A, b, P);
    printf("Shared secret key computed by Alice: %lld\n", secret_key_Alice);
    printf("Shared secret key computed by Bob: %lld\n", secret_key_Bob);

    return 0;
}

