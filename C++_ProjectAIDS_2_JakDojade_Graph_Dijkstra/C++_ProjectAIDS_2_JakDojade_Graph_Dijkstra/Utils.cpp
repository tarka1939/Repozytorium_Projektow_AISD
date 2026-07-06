#include "utils.h"
#include <string.h>

//string hashing function
int Hash(char* key) {
    const int prime = 2137;
    const int modulo = 1e8 + 9;
    long long hash_value = 0;
    long long prime_pow = 1;
    for (int i = 0; i < strlen(key); i++) {
        hash_value = (hash_value + (key[i] - 'a' + 1) * prime_pow) % modulo;
        prime_pow = (prime_pow * prime) % modulo;
    }
    return hash_value;
}
