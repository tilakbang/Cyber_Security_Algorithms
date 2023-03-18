#include <iostream>
#include <vector>
using namespace std;

#define R1 1
#define C1 2
#define R2 2
#define C2 2

int ExtendedEuclidian(int a, int b, int *x, int *y)
{
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
    int x1, y1; 
    int rem = ExtendedEuclidian(b%a, a, &x1, &y1);
    *x = y1 - (b/a) * x1;
    *y = x1;

    return rem;
}

vector<vector<int>> mulMat(vector<vector<int>> mat1, vector<vector<int>> mat2, string msg)
{
    vector<vector<int>> rslt(R1, vector<int>(C2,0));
    for (int i = 0; i < R1; i++)
    {
        for (int j = 0; j < C2; j++)
        {
            rslt[i][j] = 0;
            for (int k = 0; k < R2; k++)
            {
                rslt[i][j] += mat1[i][k] * mat2[k][j];
            }
            cout << rslt[i][j]%26 << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < msg.size(); i++)
    {
        rslt[0][i]=rslt[0][i]%26;
    }
    return rslt;
}

int main()
{
    string msg="ME";
    // int mat1[R1][C1];
    vector<vector<int>> mat1( R1 , vector<int> (C1, 0)); 
    for (int i = 0; i < msg.size(); i++)
    {
        mat1[0][i]=msg[i]-'A';
    }
    vector<vector<int>> mat2= {{9, 4},{5, 7}};
    
    vector<vector<int>> Encoded=mulMat(mat1, mat2, msg);
    cout<<"ENCODED MSG: ";
    for (int i = 0; i < msg.size(); i++)
    {
        cout<<char((Encoded[0][i])+'A');
    }
    cout<<endl;
    int x,y,a=26,b=43;
    int g=ExtendedEuclidian(a,b,&x,&y);
    vector<vector<int>> Adj= {{7, -4},{-5, 9}};
    for (int i = 0; i < msg.size(); i++)
    {
        Encoded[0][i]=Encoded[0][i]*y;
    }
    vector<vector<int>> Decoded=mulMat(Encoded, Adj, msg);
    for (int i = 0; i < msg.size(); i++)
    {
        if(Decoded[0][i]<0) Decoded[0][i]+=26;
    }
    cout<<"DECODED MSG: ";
    for (int i = 0; i < msg.size(); i++)
    {
        cout<<char((Decoded[0][i])+'A');
    }
    cout<<endl;
    return 0;
}
