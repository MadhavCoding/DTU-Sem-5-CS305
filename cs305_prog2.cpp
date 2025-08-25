#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <vector>

using namespace std;

vector<vector<char>> key_table(5, vector<char>(5));
vector<pair<int, int>> hash_pos(26);

void swap_int(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void fill_table(const string &key)
{
    vector<bool> visited(26);

    int x = 0, y = 0;
    int i = 0;
    while (i < (int)key.length())
    {
        char ch = key[i];
        int index = ch - 'A';
        if (ch == 'J') index--;

        if (!visited[index])
        {
            visited[index] = 1;
            key_table[x][y] = ch;
            hash_pos[index] = {x, y};

            y++;
            if (y == 5)
            {
                y = 0;
                x++;
            }
        }

        i++;
    }

    for (char c = 'A'; c <= 'Z'; c++)
    {
        int index = c - 'A';
        if (c == 'J') index--;

        if (!visited[index])
        {
            visited[index] = 1;
            key_table[x][y] = c;
            hash_pos[index] = {x, y};

            y++;
            if (y == 5)
            {
                y = 0;
                x++;
            }
        }
    }
}

void print_key_table()
{
    cout << "\n";
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << key_table[i][j] << ' ';
        }
        cout << "\n";
    }
    cout << "\n";
}

string encrypt_playfair(string text, string key)
{
    int len = (int)text.length();
    string result = "";

    int i = 0;
    while (i < len)
    {
        char c1 = text[i];
        if (c1 == 'J') c1 = 'I';
        char c2 = 'X';
        if (i + 1 < len && text[i + 1] != text[i])
        {
            c2 = text[i + 1];
            i += 2;
        }
        else
            i += 1;

        int index1 = c1 - 'A';
        int index2 = c2 - 'A';

        int x1 = hash_pos[index1].first, y1 = hash_pos[index1].second;
        int x2 = hash_pos[index2].first, y2 = hash_pos[index2].second;

        int x1_new, y1_new, x2_new, y2_new;

        // Same Row, Different Column
        if (x1 == x2)
        {
            x1_new = x1;
            x2_new = x2;
            y1_new = (y1 + 1) % 5;
            y2_new = (y2 + 1) % 5;
        }
        // Different Row, Same Column
        else if (y1 == y2)
        {
            x1_new = (x1 + 1) % 5;
            x2_new = (x2 + 1) % 5;
            y1_new = y1;
            y2_new = y2;
        }
        // Different Row, Different Column (Rectangle Rule)
        else
        {
            x1_new = x1;
            x2_new = x2;
            y1_new = y2;
            y2_new = y1;
        }

        char c1_new = key_table[x1_new][y1_new];
        char c2_new = key_table[x2_new][y2_new];

        result += c1_new;
        result += c2_new;
    }

    return result;
}

string decrypt_playfair(string text, string key)
{
    int len = (int)text.length();
    string result = "";

    int i = 0;
    while (i < len)
    {
        char c1 = text[i];
        if (c1 == 'J') c1 = 'I';
        char c2 = 'X';
        if (i + 1 < len && text[i + 1] != text[i])
        {
            c2 = text[i + 1];
            i += 2;
        }
        else
            i += 1;

        int index1 = c1 - 'A';
        int index2 = c2 - 'A';

        int x1 = hash_pos[index1].first, y1 = hash_pos[index1].second;
        int x2 = hash_pos[index2].first, y2 = hash_pos[index2].second;

        int x1_new, y1_new, x2_new, y2_new;

        // Same Row, Different Column
        if (x1 == x2)
        {
            x1_new = x1;
            x2_new = x2;
            y1_new = (y1 - 1 + 5) % 5;
            y2_new = (y2 - 1 + 5) % 5;
        }
        // Different Row, Same Column
        else if (y1 == y2)
        {
            x1_new = (x1 - 1 + 5) % 5;
            x2_new = (x2 - 1 + 5) % 5;
            y1_new = y1;
            y2_new = y2;
        }
        // Different Row, Different Column (Rectangle Rule)
        else
        {
            x1_new = x1;
            x2_new = x2;
            y1_new = y2;
            y2_new = y1;
        }

        char c1_new = key_table[x1_new][y1_new];
        char c2_new = key_table[x2_new][y2_new];

        result += c1_new;
        result += c2_new;
    }

    return result;
}

int main(int argc, char const *argv[])
{
    string text;
    string key = "MONARCHY";

    fill_table(key);
    print_key_table();

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "\nThe entered text is : " << text << "\n";

    string result;

    result = encrypt_playfair(text, key);
    cout << "\nThe encrypted text is : " << result << "\n";

    result = decrypt_playfair(result, key);
    cout << "\nThe decrypted text is : " << result << "\n";

    return 0;
}
