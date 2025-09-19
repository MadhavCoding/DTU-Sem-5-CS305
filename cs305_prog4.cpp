#include <bits/stdc++.h>
using namespace std;

// Function to calculate modular inverse of a under mod m
int modInverse(int a, int m) 
{
    a = a % m;
    for (int x = 1; x < m; x++) 
    {
        if ((a * x) % m == 1) return x;
    }
    return -1; // no inverse
}

// Function to find determinant of 2x2 matrix mod 26
int determinant(vector<vector<int>> &key) 
{
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    det %= 26;
    if (det < 0) det += 26;
    return det;
}

// Function to find inverse of 2x2 key matrix
vector<vector<int>> inverseKey(vector<vector<int>> &key) 
{
    int det = determinant(key);
    int invDet = modInverse(det, 26);

    vector<vector<int>> inv(2, vector<int>(2));
    inv[0][0] =  key[1][1];
    inv[1][1] =  key[0][0];
    inv[0][1] = -key[0][1];
    inv[1][0] = -key[1][0];

    for (int i = 0; i < 2; i++) 
    {
        for (int j = 0; j < 2; j++) 
        {
            inv[i][j] = (inv[i][j] * invDet) % 26;
            if (inv[i][j] < 0) inv[i][j] += 26;
        }
    }
    return inv;
}

// Function to encrypt using Hill Cipher
string encrypt(string plaintext, vector<vector<int>> &key) 
{
    if (plaintext.size() % 2 != 0) 
    {
        plaintext += 'X';
    }

    string ciphertext = "";
    for (int i = 0; i < plaintext.size(); i += 2) 
    {
        int a = plaintext[i] - 'A';
        int b = plaintext[i+1] - 'A';
        int x = (key[0][0]*a + key[0][1]*b) % 26;
        int y = (key[1][0]*a + key[1][1]*b) % 26;
        ciphertext += char(x + 'A');
        ciphertext += char(y + 'A');
    }
    return ciphertext;
}

// Function to decrypt using Hill Cipher
string decrypt(string ciphertext, vector<vector<int>> &key) 
{
    vector<vector<int>> inv = inverseKey(key);
    string plaintext = "";
    for (int i = 0; i < ciphertext.size(); i += 2) 
    {
        int a = ciphertext[i] - 'A';
        int b = ciphertext[i+1] - 'A';
        int x = (inv[0][0]*a + inv[0][1]*b) % 26;
        int y = (inv[1][0]*a + inv[1][1]*b) % 26;
        plaintext += char(x + 'A');
        plaintext += char(y + 'A');
    }
    return plaintext;
}

int main() {
    string plaintext;
    cout << "Enter Plaintext: ";
    cin >> plaintext;

    vector<vector<int>> key = {{3, 3}, {2, 5}}; 

    string ciphertext = encrypt(plaintext, key);
    cout << "Ciphertext: " << ciphertext << endl;

    string decrypted = decrypt(ciphertext, key);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
