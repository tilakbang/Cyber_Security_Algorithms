#include <iostream>
#include <vector>
#include <bitset>
#include <sstream>

using namespace std;

int main() {
    // Example matrix to convert
    vector<vector<int>> matrix {{15, 3}, {6, 3}};

    // Convert each element to a 4-bit binary string and concatenate
    stringstream ss;
    for (auto row : matrix) {
        for (auto element : row) {
            ss << bitset<4>(element).to_string();
            cout<<ss.str()<<endl;
        }
    }
    string binaryString = ss.str();

    // Print original matrix
    cout << "Original matrix:" << endl;
    for (auto row : matrix) {
        for (auto element : row) {
            cout << element << " ";
        }
        cout << endl;
    }

    // Print binary string
    cout << "Binary string: " << binaryString << endl;

    return 0;
}
