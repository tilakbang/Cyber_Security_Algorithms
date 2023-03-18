#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

string key = "0100101011110101", KEY1 = "", KEY2 = "", KEY3 = "";
string ARKEY1 = "", ARKEY2 = "", ARKEY3 = "";

map<string, string> substitution_box = {
    {"0000", "1001"},
    {"0001", "0100"},
    {"0010", "1010"},
    {"0011", "1011"},
    {"0100", "1101"},
    {"0101", "0001"},
    {"0110", "1000"},
    {"0111", "0101"},
    {"1000", "0110"},
    {"1001", "0010"},
    {"1010", "0000"},
    {"1011", "0011"},
    {"1100", "1100"},
    {"1101", "1110"},
    {"1110", "1111"},
    {"1111", "0111"}};

map<string, string> inv_substitution_box = {
    {"1001", "0000"},
    {"0100", "0001"},
    {"1010", "0010"},
    {"1011", "0011"},
    {"1101", "0100"},
    {"0001", "0101"},
    {"1000", "0110"},
    {"0101", "0111"},
    {"0110", "1000"},
    {"0010", "1001"},
    {"0000", "1010"},
    {"0011", "1011"},
    {"1100", "1100"},
    {"1110", "1101"},
    {"1111", "1110"},
    {"0111", "1111"}};

vector<vector<int>> mix_column_matrix = {{1, 4}, {4, 1}};
vector<vector<int>> inv_mix_column_matrix = {{9, 2}, {2, 9}};

int gf16_multiply(int a, int b)
{
    int p = 0;
    while (b)
    {
        if (b & 1)
            p ^= a;
        b >>= 1;
        a <<= 1;
        if (a & 16)
            a ^= 0x13;
    }
    return p & 15;
}

string DecimalToBinary(int num)
{
    string str;
    for (int i = 3; i >= 0; i--)
    {
        int k = num >> i;
        if (k & 1)
            str += '1';
        else
            str += '0';
    }
    return str;
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

string rotatenibble(string &s)
{
    string ans, temp1, temp2;
    temp1 = s.substr(0, 4);
    temp2 = s.substr(4, 4);
    ans = temp2 + temp1;
    return ans;
}

string subnibble(string &s)
{
    string ans = "", temp;
    for (int i = 0; i < s.size(); i = i + 4)
    {
        temp = substitution_box[s.substr(i, 4)];
        ans += temp;
    }

    return ans;
}

string invsubnibble(string &s)
{
    string ans = "", temp;
    for (int i = 0; i < s.size(); i = i + 4)
    {
        temp = inv_substitution_box[s.substr(i, 4)];
        ans += temp;
    }
    return ans;
}

string shiftrow(string &s)
{
    string ans = "";
    ans = s.substr(0, 4) + s.substr(12, 4) + s.substr(8, 4) + s.substr(4, 4);
    return ans;
}

vector<vector<int>> get_matrix(string &binary_string)
{
    vector<vector<int>> int_matrix(2, vector<int>(2, 0));

    // Convert the binary string to a 2x2 integer matrix
    for (int i = 0; i < binary_string.size(); i += 4)
    {
        int row_index = i / 8;
        int col_index = (i % 8) / 4;
        vector<int> row;
        for (int j = 0; j < 4; j++)
        {
            row.push_back(binary_string[i + j] - '0');
        }
        int value = row[0] * 8 + row[1] * 4 + row[2] * 2 + row[3] * 1;
        int_matrix[col_index][row_index] = value;
    }

    // Print the resulting integer matrix
    cout << "Integer Matrix:\n";
    for (int i = 0; i < int_matrix.size(); i++)
    {
        for (int j = 0; j < int_matrix[i].size(); j++)
        {
            cout << int_matrix[i][j] << "\t";
        }
        cout << endl;
    }
    return int_matrix;
}

// Function to perform matrix multiplication
vector<vector<int>> matrixMultiply(vector<vector<int>> matrix1, vector<vector<int>> matrix2)
{
    int n1 = matrix1.size();
    int m1 = matrix1[0].size();
    int n2 = matrix2.size();
    int m2 = matrix2[0].size();

    if (m1 != n2)
    {
        cout << "Error: Cannot multiply matrices with these dimensions." << endl;
        return {};
    }

    vector<vector<int>> result(n1, vector<int>(m2, 0)), matrix;

    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            for (int k = 0; k < m1; k++)
            {
                result[i][j] ^= gf16_multiply(matrix1[i][k], matrix2[k][j]);
            }
        }
    }
    matrix = result;
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < m2; j++)
        {
            result[j][i] = matrix[i][j];
        }
    }
    cout << "Matrix After Mixed column multiplication: " << endl;
    for (auto row : matrix)
    {
        for (auto element : row)
        {
            cout << element << "\t";
        }
        cout << endl;
    }
    return result;
}

void keygeneration()
{
    vector<string> Subkeys;
    cout << "----------------Key Generation---------------------" << endl;
    Subkeys.push_back(key.substr(0, 8));
    Subkeys.push_back(key.substr(8, 8));
    // cout << Subkeys[0] << " " << Subkeys[1] << endl;
    int n = 4;
    while (n--)
    {
        if (Subkeys.size() % 2 == 0)
        {
            if (Subkeys.size() == 2)
            {
                string temp1, M1 = "10000000", temp2, temp3;
                temp1 = XOR(Subkeys[0], M1);
                temp2 = rotatenibble(Subkeys[1]);
                temp3 = subnibble(temp2);
                Subkeys.push_back(XOR(temp1, temp3));
            }
            else if (Subkeys.size() == 4)
            {
                string temp4, M2 = "00110000", temp5, temp6;
                temp4 = XOR(Subkeys[2], M2);
                temp5 = rotatenibble(Subkeys[3]);
                temp6 = subnibble(temp5);
                Subkeys.push_back(XOR(temp4, temp6));
            }
        }
        else
        {
            if (Subkeys.size() == 3)
            {
                Subkeys.push_back(XOR(Subkeys[2], Subkeys[1]));
            }
            else
            {
                Subkeys.push_back(XOR(Subkeys[4], Subkeys[3]));
            }
        }
    }
    cout << "All Subkeys are: " << endl;
    for (int i = 0; i < Subkeys.size(); i++)
    {
        cout << "W[" << i << "] : " << Subkeys[i] << endl;
    }
    cout << endl;
    cout << "All Keys are: " << endl;
    KEY1 = Subkeys[0] + Subkeys[1];
    KEY2 = Subkeys[2] + Subkeys[3];
    KEY3 = Subkeys[4] + Subkeys[5];
    cout << "KEY 1: " << KEY1 << endl;
    cout << "KEY 2: " << KEY2 << endl;
    cout << "KEY 3: " << KEY3 << endl;
}

int main()
{
    keygeneration();
    string plain_text = "1101011100101000", Ciphertext = "", text = "";
    cout << endl;
    cout << "----------------Encryption---------------------" << endl;
    ARKEY1 = XOR(plain_text, KEY1);
    cout << "Add Round Key 1: " << ARKEY1 << endl;
    text = subnibble(ARKEY1);
    cout << "After Sub Nibble : " << text << endl;
    text = shiftrow(text);
    cout << "After Shift row : " << text << endl;
    vector<vector<int>> matrix = get_matrix(text);
    vector<vector<int>> result = matrixMultiply(mix_column_matrix, matrix);
    vector<int> temp;
    for (int i = 0; i < result.size(); i++)
    {
        for (int j = 0; j < result[0].size(); j++)
        {
            temp.push_back(result[i][j]);
        }
    }
    text = "";
    for (int i = 0; i < temp.size(); i++)
    {
        text += DecimalToBinary(temp[i]);
    }
    cout << "Text Now: " << text << endl;
    ARKEY2 = XOR(text, KEY2);
    cout << "Add Round Key 2: " << ARKEY2 << endl;
    text = subnibble(ARKEY2);
    cout << "After Sub Nibble : " << text << endl;
    text = shiftrow(text);
    cout << "After Shift row : " << text << endl;
    ARKEY3 = XOR(text, KEY3);
    Ciphertext = ARKEY3;
    cout << "Final Cipher Text is: ";
    cout << Ciphertext << endl;

    cout << endl;
    cout << "----------------Decryption---------------------" << endl;
    ARKEY3 = XOR(Ciphertext, KEY3);
    cout << "Add Round Key 3: " << ARKEY3 << endl;
    text = shiftrow(ARKEY3);
    cout << "After Shift row : " << text << endl;
    text = invsubnibble(text);
    cout << "After Inv Sub Nibble : " << text << endl;
    ARKEY2 = XOR(text, KEY2);
    cout << "Add Round Key 2: " << ARKEY2 << endl;
    vector<vector<int>> matrix1 = get_matrix(ARKEY2);
    vector<vector<int>> result1 = matrixMultiply(inv_mix_column_matrix, matrix1);
    vector<int> temp1;
    for (int i = 0; i < result1.size(); i++)
    {
        for (int j = 0; j < result1[0].size(); j++)
        {
            temp1.push_back(result1[i][j]);
        }
    }
    text = "";
    for (int i = 0; i < temp1.size(); i++)
    {
        text += DecimalToBinary(temp1[i]);
    }
    cout << "Text Now: " << text << endl;
    text = shiftrow(text);
    cout << "After Shift row : " << text << endl;
    text = invsubnibble(text);
    cout << "After Inv Sub Nibble : " << text << endl;
    ARKEY1 = XOR(text, KEY1);
    string newtext = ARKEY1;
    cout << "Final Decrypted Text is: ";
    cout << newtext << endl;
    return 0;
}