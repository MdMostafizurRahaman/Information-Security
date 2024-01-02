#include"header.h"

int main()
{
    cout << "Enter text to encrypt: ";
    string userInputText;
    getline(cin, userInputText);

    // Convert string to unsigned char array...
    unsigned char textToEncrypt[userInputText.length() + 1];
    strcpy(reinterpret_cast<char*>(textToEncrypt), userInputText.c_str());

    cout << "Entered text is: " << textToEncrypt << endl;

    mix_column(textToEncrypt);

    cout << "After mix column: " << textToEncrypt << endl;

    inverse_mix_column(textToEncrypt);
    cout << "After in_mix column: " << textToEncrypt << endl;

}