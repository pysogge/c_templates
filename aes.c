#include <openssl/aes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    // Generate the encryption key
    AES_KEY key;
    unsigned char* key_data;
    int key_data_len = 32;  // 32 bytes = 256 bits
    key_data = (unsigned char*)malloc(key_data_len);
    if (!RAND_bytes(key_data, key_data_len)) {
        fprintf(stderr, "Could not generate random key\n");
        exit(-1);
    }
    if (AES_set_encrypt_key(key_data, key_data_len * 8, &key) < 0) {
        fprintf(stderr, "Could not set encryption key\n");
        exit(-1);
    }

    // Encrypt the message

    // The message

    unsigned char* message = (unsigned char*)malloc(32);

    // The IV is a random number

    unsigned char* iv = (unsigned char*)malloc(32);

    if (!RAND_bytes(iv, 32)) {
        fprintf(stderr, "Could not generate random iv\n");
        exit(-1);
    }

    // The ciphertext

    unsigned char* ciphertext = (unsigned char*)malloc(32);

    // The length of the ciphertext

    int ciphertext_len;

    // Encrypt the message

    if (!AES_cbc_encrypt(message, ciphertext, 32, &key, iv, AES_ENCRYPT)) {
        fprintf(stderr, "Could not encrypt message\n");
        exit(-1);
    }

    // The ciphertext length is a multiple of the block size

    ciphertext_len = 32;

    // Decrypt the message

    // The plaintext

    unsigned char* plaintext = (unsigned char*)malloc(32);

    // The length of the plaintext

    int plaintext_len;

    // Decrypt the message

    if (!AES_cbc_encrypt(ciphertext, plaintext, 32, &key, iv, AES_DECRYPT)) {
        fprintf(stderr, "Could not decrypt message\n");
        exit(-1);
    }

    // The plaintext length is a multiple of the block size

    plaintext_len = 32;

    // Print the decrypted message

    printf("Decrypted message: %s\n", plaintext);

    // Free the memory

    free(key_data);

    free(message);

    free(iv);

    free(ciphertext);

    free(plaintext);

    return 0;
}
