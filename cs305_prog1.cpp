#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

using namespace std;

string encrypt_ceaser(string text, int key) 
{
    int len = text.length();
    string result = ""; 

    for (int i = 0; i < len; i++) 
    {
        char c = text[i];

        if (isupper(c)) 
        {
            result += ((c - 'A' + key) % 26) + 'A';
        } 
        else if (islower(c)) 
        {
            result += ((c - 'a' + key) % 26) + 'a';
        } 
        else 
        {
            result += c; 
        }
    }

    return result;
}

string decrypt_ceaser(string text, int key) 
{
    return encrypt_ceaser(text, 26 - (key % 26));
}

int main() 
{
    string text;
    int key;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "The entered text is : " << text << "\n";

    cout << "Enter the key (0-25): ";
    cin >> key;

    string result;

    result = encrypt_ceaser(text, key);
    cout << "The encrypted text is : " << result << "\n";
    
    result = decrypt_ceaser(result, key);
    cout << "The decrypted text is : " << result << "\n";

    return 0;
}
