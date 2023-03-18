#include <iostream>
#include <vector>
using namespace std;

int gf16_multiply(int a, int b) {
    int p = 0;
    while (b) {
        if (b & 1)
            p ^= a;
        b >>= 1;
        a <<= 1;
        if (a & 16)
            a ^= 0x13;
    }
    return p & 15;
}

int main() {
    vector<vector<int>> table(16,vector<int>(16,0));
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            table[i][j] = gf16_multiply(i, j);
        }
    }
    cout << "GF(16) Multiplication Table:\n";
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            cout << table[i][j] << "\t";
        }
        cout << endl;
    }
    return 0;
}
