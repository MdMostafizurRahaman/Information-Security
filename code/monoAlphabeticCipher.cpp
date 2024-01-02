#include<bits/stdc++.h>
using namespace std;

string encryption (string message, string key){
    map<char, char>mpp;
    for(int i = 0; i < 26; i++){
        mpp['A' + i] = key[i];
        mpp['a' + i] = tolower(key[i]);
    }
    
    string monoEncryption;
    for(int i = 0; i < message.size(); i++){
        if(isalpha(message[i])){
            monoEncryption += mpp[message[i]];
        }
        else{
            monoEncryption += message[i];
        }
    }
    return monoEncryption;
}
string decryption(string monoEncryption, string key){
    map<char, char>mpp;
    for(int i = 0; i < 26; i++){
        mpp[key[i]] = 'A' + i;
        mpp[tolower(key[i])] = 'a' + i;
    }
    string monoDecryption;
    for(int i = 0; i < monoEncryption.size(); i++){
        if(isalpha(monoEncryption[i])){
            monoDecryption += mpp[monoEncryption[i]];
        }
        else{
            monoDecryption += monoEncryption[i]; 
        }
    }
    return monoDecryption;


}

int main(){
    cout << "Enter your secret message:";
    string message;
    getline(cin, message);

    string key = "JKLMNBVCXTASDFGHZPOIUYQWER";
    cout << "Encrypted:" << encryption(message, key) << endl;
    cout << "Decryption:" << decryption(encryption(message, key), key) << endl;
}