#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "lookup_table_encoding.h"
#include "key_expand.h"
#include <iomanip>
using namespace std;

void subsititeBits(unsigned char *temp)
{
    for (int i = 0; i < 16; i++)
    {
        temp[i] = sbox[temp[i]];
    }
}

void shiftRow(unsigned char *temp)
{
    unsigned char *temp2 = new unsigned char[16];
    for (int i = 0; i < 16; i++)
        temp2[i] = temp[i];
    // 1st column
    temp[0] = temp2[0];
    temp[4] = temp2[4];
    temp[8] = temp2[8];
    temp[12] = temp2[12];

    // 2nd column
    temp[1] = temp2[5];
    temp[5] = temp2[9];
    temp[9] = temp2[13];
    temp[13] = temp2[1];

    // 3rd column
    temp[2] = temp2[10];
    temp[6] = temp2[14];
    temp[10] = temp2[2];
    temp[14] = temp2[6];

    // 4th column
    temp[3] = temp2[15];
    temp[7] = temp2[3];
    temp[11] = temp2[7];
    temp[15] = temp2[11];
}

void mixColumn(unsigned char *temp)
{
    unsigned char *temp2 = new unsigned char[16];

    for (int i = 0; i < 16; i++)
    {
        temp2[i] = temp[i];
    }

    // 1st row
    temp[0] = (unsigned char)lookup2[temp2[0]] ^ lookup3[temp2[1]] ^ temp2[2] ^ temp2[3];
    temp[1] = (unsigned char)temp2[0] ^ lookup2[temp2[1]] ^ lookup3[temp2[2]] ^ temp2[3];
    temp[2] = (unsigned char)temp2[0] ^ temp2[1] ^ lookup2[temp2[2]] ^ lookup3[temp2[3]];
    temp[3] = (unsigned char)lookup3[temp2[0]] ^ temp2[1] ^ temp2[2] ^ lookup2[temp2[3]];

    // 2nd row
    temp[4] = (unsigned char)lookup2[temp2[4]] ^ lookup3[temp2[5]] ^ temp2[6] ^ temp2[7];
    temp[5] = (unsigned char)temp2[4] ^ lookup2[temp2[5]] ^ lookup3[temp2[6]] ^ temp2[7];
    temp[6] = (unsigned char)temp2[4] ^ temp2[5] ^ lookup2[temp2[6]] ^ lookup3[temp2[7]];
    temp[7] = (unsigned char)lookup3[temp2[4]] ^ temp2[5] ^ temp2[6] ^ lookup2[temp2[7]];

    // 3rd row
    temp[8] = (unsigned char)lookup2[temp2[8]] ^ lookup3[temp2[9]] ^ temp2[10] ^ temp2[11];
    temp[9] = (unsigned char)temp2[8] ^ lookup2[temp2[9]] ^ lookup3[temp2[10]] ^ temp2[11];
    temp[10] = (unsigned char)temp2[8] ^ temp2[9] ^ lookup2[temp2[10]] ^ lookup3[temp2[11]];
    temp[11] = (unsigned char)lookup3[temp2[8]] ^ temp2[9] ^ temp2[10] ^ lookup2[temp2[11]];

    // 4th row
    temp[12] = (unsigned char)lookup2[temp2[12]] ^ lookup3[temp2[13]] ^ temp2[14] ^ temp2[15];
    temp[13] = (unsigned char)temp2[12] ^ lookup2[temp2[13]] ^ lookup3[temp2[14]] ^ temp2[15];
    temp[14] = (unsigned char)temp2[12] ^ temp2[13] ^ lookup2[temp2[14]] ^ lookup3[temp2[15]];
    temp[15] = (unsigned char)lookup3[temp2[12]] ^ temp2[13] ^ temp2[14] ^ lookup2[temp2[15]];
}

void addRoundKey(unsigned char *temp, unsigned char *extendedkeys, int kp)
{
    for (int i = 0; i < 16; i++)
    {
        temp[i] ^= extendedkeys[kp * 16 + i];
    }
}

void encryption(unsigned char *temp, unsigned char *extendedkeys, unsigned char *previousBlock)
{
    int kp = 0;
    // XOR with the previous ciphertext block
    for (int i = 0; i < 16; i++)
    {
        temp[i] ^= previousBlock[i];
    }

    for (int i = 0; i < 16; i++)
    {
        temp[i] ^= extendedkeys[i];
    }
    kp++;
    while (kp < 11)
    {
        // Substitution bits
        subsititeBits(temp);
        // Shift row
        shiftRow(temp);

        // Mix column
        if (kp < 10)
        {
            mixColumn(temp);
        }

        addRoundKey(temp, extendedkeys, kp);
        kp++;
    }
}

string toHex(unsigned char byte)
{
    stringstream ss;
    ss << setw(2) << setfill('0') << hex << (int)byte;
    return ss.str();
}

string encryptedHexString(unsigned char *data, int length)
{
    stringstream ss;
    for (int i = 0; i < length; i++)
    {
        ss << toHex(data[i]) << " ";
    }
    return ss.str();
}

string encrypt(string tp)
{
    ifstream File;
    int extendedlength = 0;
    string outputStr;

    string filepath = "AES/encryption.aes";
    // Clearing encryption.aes before editing
    File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
    if (!File.is_open() || File.fail())
    {
        File.close();
        printf("\nError : failed to erase file content !");
    }
    File.close();
    // Reading plain text from input.txt
    fstream newfile;
    newfile.open("input.txt", ios::in); // Open a file to perform read operation using file object
    // Checking whether the file is open

    // Read data from file object and put it into string.
    int messlength = tp.length();
    if ((messlength % 16) != 0)
    {
        extendedlength = messlength + (16 - (messlength % 16));
    }
    else
    {
        extendedlength = messlength;
    }
    unsigned char *encryptedtext = new unsigned char[extendedlength];
    for (int i = 0; i < extendedlength; i++)
    {
        if (i < messlength)
            encryptedtext[i] = tp[i];
        else
            encryptedtext[i] = 0;
    }

    // Getting key from key.txt
    string k;
    ifstream infile;
    infile.open("AES/key.txt");
    if (infile.is_open())
    {
        getline(infile, k); // The first line of file should be the key
        infile.close();
    }
    else
        cout << "Unable to open file" << endl;

    istringstream tempkey(k);
    unsigned char key[16];
    unsigned int x;
    for (int i = 0; i < 16; i++)
    {
        tempkey >> hex >> x;
        key[i] = x;
    }

    // Extending key
    unsigned char extendedkeys[176];
    Key_extenxion(key, extendedkeys);

    // Initialization vector (IV)
    unsigned char iv[16] = {0}; // You should use a random or predefined IV

    // Encrypting our plain text
    for (int i = 0; i < extendedlength; i += 16)
    {
        unsigned char *temp = new unsigned char[16];
        for (int j = 0; j < 16; j++)
        {
            temp[j] = encryptedtext[i + j];
        }
        encryption(temp, extendedkeys, iv);

        outputStr = encryptedHexString(temp, 16);

        for (int j = 0; j < 16; j++)
        {
            encryptedtext[i + j] = temp[j];
        }

        // Update the IV for the next block
        for (int j = 0; j < 16; j++)
        {
            iv[j] = temp[j];
        }
    }

    // Storing our encrypted data in encryption.aes
    ofstream fout;  // Create Object of Ofstream
    ifstream fin;
    fin.open("AES/encryption.aes");
    fout.open("AES/encryption.aes", ios::app); // Append mode
    if (fin.is_open())
        fout << encryptedtext << "\n"; // Writing data to file
    fin.close();
    fout.close();

    return outputStr;
}