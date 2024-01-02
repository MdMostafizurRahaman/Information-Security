#include <iostream>
#include "a_es.h"

using namespace std;

#define Total_round 10
#define padding_char '0'

void incrementCounter(unsigned char counter[AES_BLOCK_SIZE]) {
    // This is a simple increment function. You might need a more sophisticated one in a real application.
    for (int i = AES_BLOCK_SIZE - 1; i >= 0; i--) {
        if (counter[i] == 255) {
            counter[i] = 0;
        } else {
            counter[i]++;
            break;
        }
    }
}

int main() {
    unsigned char textToEncrypt[] = "Two One Nine five nine";
    unsigned char key[] = "Thats my Kung Fu";

    key_expansion(key);
    cout << endl;
    print_key();

    int text_length = sizeof(textToEncrypt) - 1;
    int extended_length;

    // Calculate the extended length for padding
    if (text_length % AES_BLOCK_SIZE != 0) {
        extended_length = text_length + (AES_BLOCK_SIZE - (text_length % AES_BLOCK_SIZE));
    } else {
        extended_length = text_length;
    }

    unsigned char counter[AES_BLOCK_SIZE] = {0}; // Counter initialized to zero

    unsigned char encrypted_text[extended_length + 1];
    for (int i = 0; i < extended_length; i += AES_BLOCK_SIZE) {
        // Encryption
        unsigned char block[AES_BLOCK_SIZE];

        // Set the counter value for this block
        memcpy(block, counter, AES_BLOCK_SIZE);

        encyption(block);

        // XOR the encrypted counter with the plaintext
        for (int k = 0; k < AES_BLOCK_SIZE; k++) {
            encrypted_text[i + k] = block[k] ^ textToEncrypt[i + k];
        }

        // Increment the counter for the next block
        incrementCounter(counter);
    }

    cout << "Cipher Text: ";
    cipher_text(encrypted_text, sizeof(encrypted_text));
    cout << endl;

    // Reset counter for decryption
    memset(counter, 0, AES_BLOCK_SIZE);

    unsigned char decrypted_text[extended_length + 1];
    for (int i = 0; i < extended_length; i += AES_BLOCK_SIZE) {
        // Decryption
        unsigned char block[AES_BLOCK_SIZE];

        // Set the counter value for this block
        memcpy(block, counter, AES_BLOCK_SIZE);

        encyption(block);

        // XOR the encrypted counter with the ciphertext
        for (int k = 0; k < AES_BLOCK_SIZE; k++) {
            decrypted_text[i + k] = block[k] ^ encrypted_text[i + k];
        }

        // Increment the counter for the next block
        incrementCounter(counter);
    }

    // Identify and remove padding
    int padding_length = 0;
    for (int i = extended_length - 1; i >= 0; i--) {
        if (decrypted_text[i] == padding_char) {
            padding_length++;
        } else {
            break;
        }
    }

    // Null-terminate the decrypted text
    decrypted_text[extended_length - padding_length] = '\0';

    cout << "\nDecrypted Text: " << decrypted_text << endl;

    return 0;
}

