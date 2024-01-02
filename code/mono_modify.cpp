#include<bits/stdc++.h>
using namespace std;
int main(){
    string plain =  "ABCDEFGHIJkLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string cipher = "MNOPQRSABCDEFGHIJKLXYZTUVWpqrstabcdeuvwxyzfghijklmno";
    string input, encrypt = "", decrypt = "";
    getline(cin, input);
    cout <<"Cyper Text:";
    for(int i = 0; i < input.size(); i++){
        for(int j = 0; j < plain.size(); j++){
            if(input[i] == plain[j]){
                encrypt[i] = cipher[j];
                cout << encrypt[i];
            }
        }
    }
    cout << endl;
    

 cout << "Plain Text:";
    for(int i = 0; i < input.size(); i++){
        for(int j = 0; j < cipher.size(); j++){
            if(encrypt[i] == cipher[j]){
                decrypt[i] = plain[j];
                cout << decrypt[i];
            }
        }
    }
    //cout << "Plain Text:" << decrypt << endl;
}