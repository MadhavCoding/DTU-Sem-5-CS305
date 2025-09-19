#include <bits/stdc++.h>
using namespace std;

string vigenereEncrypt(const string &plain, const string &key) 
{
    string newKey, cipher;
    for (int i = 0; i < plain.size(); i++)
        newKey.push_back(key[i % key.size()]);
    for (int i = 0; i < plain.size(); i++)
        cipher.push_back(((plain[i] - 'A') + (newKey[i] - 'A')) % 26 + 'A');
    return cipher;
}

string vigenereDecrypt(const string &cipher, const string &key) 
{
    string newKey, plain;
    for (int i = 0; i < cipher.size(); i++)
        newKey.push_back(key[i % key.size()]);
    for (int i = 0; i < cipher.size(); i++)
        plain.push_back(((cipher[i] - 'A') - (newKey[i] - 'A') + 26) % 26 + 'A');
    return plain;
}

string autokeyEncrypt(const string &plain, const string &key) 
{
    string newKey = key;
    for (int i = 0; newKey.size() < plain.size(); i++)
        newKey.push_back(plain[i]);
    string cipher;
    for (int i = 0; i < plain.size(); i++)
        cipher.push_back(((plain[i] - 'A') + (newKey[i] - 'A')) % 26 + 'A');
    return cipher;
}

string autokeyDecrypt(const string &cipher, const string &key) 
{
    string newKey = key, plain;
    for (int i = 0; i < cipher.size(); i++) 
    {
        char p = ((cipher[i] - 'A') - (newKey[i] - 'A') + 26) % 26 + 'A';
        plain.push_back(p);
        newKey.push_back(p);
    }
    return plain;
}

int main() 
{
    string plain, key;

    cout << "Enter Plaintext : ";
    cin >> plain;

    cout << "Enter Key : ";
    cin >> key;

    string vEnc = vigenereEncrypt(plain, key);
    string vDec = vigenereDecrypt(vEnc, key);

    string aEnc = autokeyEncrypt(plain, key);
    string aDec = autokeyDecrypt(aEnc, key);

    cout << "Plaintext : " << plain << "\n";
    cout << "Vigenere Encrypted : " << vEnc << "\n";
    cout << "Vigenere Decrypted : " << vDec << "\n";
    cout << "Autokey Encrypted : " << aEnc << "\n";
    cout << "Autokey Decrypted : " << aDec << "\n";
}
