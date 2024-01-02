#include <iostream>
#include "a_es.h"

using namespace std;

#define Total_round 10
#define padding_char '0'

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
        extended_length = (text_length / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
    } else {
        extended_length = text_length;
    }

    unsigned char padded_text[extended_length];
    for (int i = 0; i < text_length; i++) {
        padded_text[i] = textToEncrypt[i];
    }

    // Add padding
    for (int i = text_length; i < extended_length; i++) {
        padded_text[i] = padding_char;
    }

    unsigned char encrypted_text[extended_length+1];
    for (int i = 0; i < extended_length; i += AES_BLOCK_SIZE) {
        // Encryption
        unsigned char block[AES_BLOCK_SIZE];
        for (int k = 0; k < AES_BLOCK_SIZE; k++) {
            block[k] = padded_text[i + k];
        }

        encyption(block);

        for (int k = 0; k < AES_BLOCK_SIZE; k++) {
            encrypted_text[i + k] = block[k];
        }
    }

    cout << "Cipher Text (ECB): ";
    cipher_text(encrypted_text, sizeof(encrypted_text));
    cout << endl;

    // Decryption in ECB mode is similar
    unsigned char decrypted_text[extended_length];
    for (int i = 0; i < extended_length; i += AES_BLOCK_SIZE) {
        // Decryption
        unsigned char block[AES_BLOCK_SIZE];
        for (int k = 0; k < AES_BLOCK_SIZE; k++) {
            block[k] = encrypted_text[i + k];
        }

        decryption(block);

        for (int k = 0; k < AES_BLOCK_SIZE; k++) {
            decrypted_text[i + k] = block[k];
        }
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

