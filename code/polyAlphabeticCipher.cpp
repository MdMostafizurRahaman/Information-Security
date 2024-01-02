#include<bits/stdc++.h>
using namespace std;

string encryption(string message, string key){
    string ployencryption;

    for(int i = 0; i < message.size(); i++){
        if(isalpha(message[i])){
            int key_value = key[i % key.size()] - 'A';

            if(isupper(message[i])){
                ployencryption += 'A' + (message[i] - 'A' + key_value) % 26; 
            }
            else{
                ployencryption += 'a' + (message[i] - 'a' + key_value) % 26;
            }
        }
        else{
            ployencryption += message[i];
        }
    }
    return ployencryption;
}

string decryption(string polyencryption, string key){
    string polydecryption;
    for(int i = 0; i < polyencryption.size(); i++){
        if(isalpha(polyencryption[i])){
            char key_value = key[i % key.size()] - 'A';
            if(isupper(polyencryption[i])){
                polydecryption += 'A' + (polyencryption[i] - 'A' - key_value + 26) % 26;

            }
            else{
                polydecryption += 'a' + (polyencryption[i] - 'a' - key_value + 26) % 26;
            }
        }
        else{
            polydecryption += polyencryption[i];
        }
        
    }
    return polydecryption;
}
int main(){
    cout << "Enter your secret message:";
    string message;
    getline(cin, message);

    string key = "Rakib";
    cout << "Encrypted:" << encryption(message, key) << endl;
    cout << "Decrypted:" << decryption(encryption(message, key), key);

}