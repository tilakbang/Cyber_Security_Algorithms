#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string key = "0010010111";
vector<int> P10 = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
vector<int> P8 = {6, 3, 7, 4, 8, 5, 10, 9};
vector<int> IP = {2, 6, 3, 1, 4, 8, 5, 7};
vector<int> IPinv = {4, 1, 3, 5, 7, 2, 8, 6};
vector<int> EP = {4, 1, 2, 3, 2, 3, 4, 1};
vector<int> P4 = {2, 4, 3, 1};
vector<vector<int>> S0 = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};
vector<vector<int>> S1 = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};
string KEY1, KEY2;

// This function is for 4 bit only
string DecimalToBinary(int num)
{
    string str;
    for (int i = 1; i >= 0; i--)
    {
        int k = num >> i;
        if (k & 1)
            str += '1';
        else
            str += '0';
    }
    return str;
}

int binaryToDecimal(string n)
{
    string num = n;
    int dec_value = 0;
    int base = 1;
    int len = num.length();
    for (int i = len - 1; i >= 0; i--)
    {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
    return dec_value;
}

string applypermutation(string &s, vector<int> P)
{
    int n = P.size();
    string a = "";
    for (int i = 0; i < n; i++)
    {
        a.push_back(s[P[i] - 1]);
    }
    return a;
}

void shiftstring(string &s, int b)
{
    for (int i = 0; i < b; i++)
    {
        s.push_back(s[0]);
        s.erase(s.begin());
    }
}

string XOR(string &s1, string &s2)
{
    string ans = "";
    int n = s1.size();
    for (int i = 0; i < n; i++)
    {
        if (s1[i] == s2[i])
            ans += '0';
        else
            ans += '1';
    }
    return ans;
}

vector<string> keygeneration()
{
    string k = applypermutation(key, P10);
    int d = key.size() / 2;
    string a1 = k.substr(0, d), a2 = k.substr(d, d);
    shiftstring(a1, 1);
    shiftstring(a2, 1);
    string LS1 = a1 + a2;
    string KEY1 = applypermutation(LS1, P8);
    shiftstring(a1, 2);
    shiftstring(a2, 2);
    string LS2 = a1 + a2;
    string KEY2 = applypermutation(LS2, P8);
    return {KEY1, KEY2};
}

string Encryption(string &data)
{
    // Apply IP
    string A1 = applypermutation(data, IP);
    cout << "Applied IP: " << A1 << endl;
    int d = A1.size() / 2;
    string a1 = A1.substr(0, d), a2 = A1.substr(d, d);
    // Expansion Permutation on a2
    string EP1 = applypermutation(a2, EP);
    cout << "Applied Expansion Permutation: " << EP1 << endl;
    // XOR with KEY1;
    string A2 = XOR(EP1, KEY1);
    cout << "XOR with KEY 1: " << A2 << endl;
    // S-box substitution
    // Only for 8-bit here
    string x1 = "", y1 = "", x2 = "", y2 = "";
    x1 += A2[0];
    x1 += A2[3];
    y1 += A2[1];
    y1 += A2[2];
    x2 += A2[4];
    x2 += A2[7];
    y2 += A2[5];
    y2 += A2[6];
    int num1 = S0[binaryToDecimal(x1)][binaryToDecimal(y1)];
    int num2 = S1[binaryToDecimal(x2)][binaryToDecimal(y2)];
    string b1 = DecimalToBinary(num1);
    string b2 = DecimalToBinary(num2);
    // After substitution string
    string B1 = b1 + b2;
    cout << "After Substitution String: " << B1 << endl;
    // Apply P4
    string B2 = applypermutation(B1, P4);
    cout << "Applied P4: " << B2 << endl;
    // XOR with a1
    string B3 = XOR(B2, a1);
    cout << "XOR with left nibble: " << B3 << endl;
    // Before swap;
    string A3 = B3 + a2;
    cout << "Before swap: " << A3 << endl;
    // AFter swap;
    string A4 = a2 + B3;
    cout << "After swap: " << A4 << endl;
    d = A4.size() / 2;
    a1 = A4.substr(0, d), a2 = A4.substr(d, d);
    // Expansion Permutation on a2
    string EP2 = applypermutation(a2, EP);
    cout << "Applied Expansion Permutation: " << EP2 << endl;
    // XOR with KEY1;
    A2 = XOR(EP2, KEY2);
    cout << "XOR with KEY 2: " << A2 << endl;
    // S-box substitution
    // Only for 8-bit here
    x1 = "", y1 = "", x2 = "", y2 = "";
    x1 += A2[0];
    x1 += A2[3];
    y1 += A2[1];
    y1 += A2[2];
    x2 += A2[4];
    x2 += A2[7];
    y2 += A2[5];
    y2 += A2[6];
    num1 = S0[binaryToDecimal(x1)][binaryToDecimal(y1)];
    num2 = S1[binaryToDecimal(x2)][binaryToDecimal(y2)];
    b1 = DecimalToBinary(num1);
    b2 = DecimalToBinary(num2);
    // After substitution string
    B1 = b1 + b2;
    cout << "After Substitution String: " << B1 << endl;
    // Apply P4
    B2 = applypermutation(B1, P4);
    cout << "Applied P4: " << B2 << endl;
    // XOR with a1
    B3 = XOR(B2, a1);
    cout << "XOR with left nibble: " << B3 << endl;
    // Before IP inverse;
    A3 = B3 + a2;
    cout << "Before IP inverse String: " << A3 << endl
         << endl;
    string Cipher_text = applypermutation(A3, IPinv);
    return Cipher_text;
}

string Decryption(string &Cipher_text)
{
    // Apply IP
    string A1 = applypermutation(Cipher_text, IP);
    cout << "Applied IP: " << A1 << endl;
    int d = A1.size() / 2;
    string a1 = A1.substr(0, d), a2 = A1.substr(d, d);
    // Expansion Permutation on a2
    string EP1 = applypermutation(a2, EP);
    cout << "Applied Expansion Permutation: " << EP1 << endl;
    // XOR with KEY1;
    string A2 = XOR(EP1, KEY2);
    cout << "XOR with KEY 2: " << A2 << endl;
    // S-box substitution
    // Only for 8-bit here
    string x1 = "", y1 = "", x2 = "", y2 = "";
    x1 += A2[0];
    x1 += A2[3];
    y1 += A2[1];
    y1 += A2[2];
    x2 += A2[4];
    x2 += A2[7];
    y2 += A2[5];
    y2 += A2[6];
    int num1 = S0[binaryToDecimal(x1)][binaryToDecimal(y1)];
    int num2 = S1[binaryToDecimal(x2)][binaryToDecimal(y2)];
    string b1 = DecimalToBinary(num1);
    string b2 = DecimalToBinary(num2);
    // After substitution string
    string B1 = b1 + b2;
    cout << "After Substitution String: " << B1 << endl;
    // Apply P4
    string B2 = applypermutation(B1, P4);
    cout << "Applied P4: " << B2 << endl;
    // XOR with a1
    string B3 = XOR(B2, a1);
    cout << "XOR with left nibble: " << B3 << endl;
    // Before swap;
    string A3 = B3 + a2;
    cout << "Before swap: " << A3 << endl;
    // AFter swap;
    string A4 = a2 + B3;
    cout << "After swap: " << A4 << endl;
    d = A4.size() / 2;
    a1 = A4.substr(0, d), a2 = A4.substr(d, d);
    // Expansion Permutation on a2
    string EP2 = applypermutation(a2, EP);
    cout << "Applied Expansion Permutation: " << EP2 << endl;
    // XOR with KEY1;
    A2 = XOR(EP2, KEY1);
    cout << "XOR with KEY 1: " << A2 << endl;
    // S-box substitution
    // Only for 8-bit here
    x1 = "", y1 = "", x2 = "", y2 = "";
    x1 += A2[0];
    x1 += A2[3];
    y1 += A2[1];
    y1 += A2[2];
    x2 += A2[4];
    x2 += A2[7];
    y2 += A2[5];
    y2 += A2[6];
    num1 = S0[binaryToDecimal(x1)][binaryToDecimal(y1)];
    num2 = S1[binaryToDecimal(x2)][binaryToDecimal(y2)];
    b1 = DecimalToBinary(num1);
    b2 = DecimalToBinary(num2);
    // After substitution string
    B1 = b1 + b2;
    cout << "After Substitution String: " << B1 << endl;
    // Apply P4
    B2 = applypermutation(B1, P4);
    cout << "Applied P4: " << B2 << endl;
    // XOR with a1
    B3 = XOR(B2, a1);
    cout << "XOR with left nibble: " << B3 << endl;
    // Before IP inverse;
    A3 = B3 + a2;
    cout << "Before IP inverse String: " << A3 << endl
         << endl;
    string Plain_text = applypermutation(A3, IPinv);
    return Plain_text;
}

int main()
{
    string data = "10100101";
    vector<string> KEYS = keygeneration();
    KEY1 = KEYS[0];
    KEY2 = KEYS[1];
    cout << "KEY Generation: " << endl;
    cout << "KEY 1: " << KEY1 << endl;
    cout << "KEY 2: " << KEY2 << endl
         << endl;
    string Cipher_text = Encryption(data);
    cout << "Cipher Text: " << Cipher_text << endl
         << endl;
    string Plain_text = Decryption(Cipher_text);
    cout << "Plain Text: " << Plain_text << endl
         << endl;
    return 0;
}