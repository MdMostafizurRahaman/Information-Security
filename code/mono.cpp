#include<bits/stdc++.h>
using namespace std;
int main(){
    char plain[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'k', 'L', 'M', 
                    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
                    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
                    };
    char cyper[] = {'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'A', 'B', 'C', 'D', 'E', 'F', 
                    'G', 'H', 'I', 'J', 'K', 'L', 'X', 'Y', 'Z', 'T', 'U', 'V', 'W', 
                    'p', 'q', 'r', 's', 't', 'a', 'b', 'c', 'd', 'e', 'u', 'v', 'w', 
                    'x', 'y', 'z', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'
                    };
    char input[100] = {'\0'}, encrypt[100] = {'\0'}, decrypt[100] = {'\0'};
    gets(input);
    for(int i = 0; i < strlen(input); i++){
        for(int j = 0; j < 52; j++){
            if(input[i] == plain[j]){
                encrypt[i] = cyper[j];
            }
        }
    }
    cout <<"Cyper Text:" << encrypt << endl;

    for(int i = 0; i < strlen(encrypt); i++){
        for(int j = 0; j < 52; j++){
            if(encrypt[i] == cyper[j]){
                decrypt[i] = plain[j];
            }
        }
    }
    cout << "Plain Text:" << decrypt << endl;
}