#include <bits/stdc++.h>
using namespace std;

string encrypt(string &plaintext, string &key) 
{
    string ciphertext;
    int n = plaintext.size();
    for (int i = 0; i < n; i++) 
    {
        if (isalpha(plaintext[i])) 
        {
            char p = plaintext[i];
            char k = key[i % key.size()];
            char c = ((p - 'A') + (k - 'A')) % 26 + 'A';
            ciphertext.push_back(c);
        } 
        else 
        {
            ciphertext.push_back(plaintext[i]);
        }
    }
    return ciphertext;
}

string decrypt(string &ciphertext, string &key) 
{
    string plaintext;
    int n = ciphertext.size();
    for (int i = 0; i < n; i++) 
    {
        if (isalpha(ciphertext[i])) 
        {
            char c = ciphertext[i];
            char k = key[i % key.size()];
            char p = ((c - 'A') - (k - 'A') + 26) % 26 + 'A';
            plaintext.push_back(p);
        } 
        else 
        {
            plaintext.push_back(ciphertext[i]); 
        }
    }
    return plaintext;
}

int main() 
{
    string plaintext, key;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);
    cout << "Enter running key text: ";
    getline(cin, key);

    string ciphertext = encrypt(plaintext, key);
    cout << "Encrypted text: " << ciphertext << endl;

    string decrypted = decrypt(ciphertext, key);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
