#include <bits/stdc++.h>
using namespace std;

// Permutation tables for S-DES
const vector<int> P10 = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
const vector<int> P8  = {6, 3, 7, 4, 8, 5, 10, 9};

string permute(const string &bits, const vector<int> &perm) 
{
    string out = "";
    for (int p : perm) out += (bits[p-1]);
    return out;
}

string leftShift(const string &half, int n) 
{
    int len = half.size();
    n %= len;
    return half.substr(n) + half.substr(0, n);
}

// Generate K1 and K2 from 10-bit key
pair<string,string> generate_subkeys(const string &key10) 
{
    // 1. P10
    string p10 = permute(key10, P10);

    // 2. Split
    string L = p10.substr(0,5);
    string R = p10.substr(5,5);

    // 3. Left shift by 1 (LS-1)
    L = leftShift(L, 1);
    R = leftShift(R, 1);

    // 4. Combine and P8 -> K1
    string combined = L + R;
    string K1 = permute(combined, P8);

    // 5. Left shift by 2 more (LS-2)
    L = leftShift(L, 2);
    R = leftShift(R, 2);

    // 6. Combine and P8 -> K2
    combined = L + R;
    string K2 = permute(combined, P8);

    return {K1, K2};
}

int main() 
{
    string key10;
    cout << "Enter 10-bit key : ";
    cin >> key10;
    
    auto [K1, K2] = generate_subkeys(key10);

    cout << "K1: " << K1 << "\n";
    cout << "K2: " << K2 << "\n";
    return 0;
}
