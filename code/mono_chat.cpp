#include<bits/stdc++.h>
using namespace std;

string encrypt(string plaintext, map<char, char> key) {
    string ciphertext = "";
    for (int i = 0; i < plaintext.size(); i++) {
        char c = plaintext[i];
        if (key.count(c) > 0) {
            ciphertext += key.at(c);
        } else {
            ciphertext += c; // Keep non-alphabet characters unchanged
        }
    }
    return ciphertext;
}


string decrypt(string ciphertext, map<char, char> key) {
    string plaintext = "";
    for (size_t i = 0; i < ciphertext.size(); i++) {
        char c = ciphertext[i];
        if (key.count(c) > 0) {
            plaintext += key[c];
        } else {
            plaintext += c; // Keep non-alphabet characters unchanged
        }
    }
    return plaintext;
}


int main() {
    map<char, char> key = {
        {'A', 'Q'}, {'B', 'W'}, {'C', 'E'}, {'D', 'R'}, {'E', 'T'}, {'F', 'Y'}, {'G', 'U'}, {'H', 'I'}, {'I', 'O'}, {'J', 'P'}, {'K', 'A'}, {'L', 'S'}, {'M', 'D'}, {'N', 'F'}, {'O', 'G'}, {'P', 'H'}, {'Q', 'J'}, {'R', 'K'}, {'S', 'L'}, {'T', 'Z'}, {'U', 'X'}, {'V', 'C'}, {'W', 'V'}, {'X', 'B'}, {'Y', 'N'}, {'Z', 'M'},
        {'a', 'q'}, {'b', 'w'}, {'c', 'e'}, {'d', 'r'}, {'e', 't'}, {'f', 'y'}, {'g', 'u'}, {'h', 'i'}, {'i', 'o'}, {'j', 'p'}, {'k', 'a'}, {'l', 's'}, {'m', 'd'}, {'n', 'f'}, {'o', 'g'}, {'p', 'h'}, {'q', 'j'}, {'r', 'k'}, {'s', 'l'}, {'t', 'z'}, {'u', 'x'}, {'v', 'c'}, {'w', 'v'}, {'x', 'b'}, {'y', 'n'}, {'z', 'm'}
    };

    string plaintext;
    getline(cin, plaintext);
    string encrypted = encrypt(plaintext, key);
    string decrypted = decrypt(encrypted, key);

    cout << "Original: " << plaintext << endl;
    cout << "Encrypted: " << encrypted << endl;
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}
