#include <iostream>
#include <math.h>
#include <time.h>
using namespace std;

bool is_prime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}

int generate_prime()
{

    int random_number = rand();
    while (!is_prime(random_number))
    {
        random_number = rand();
    }
    return random_number;
}

// Returns gcd of a and b
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Generates public and private keys
void generate_keys(long long &e, long long &d, long long &n)
{
    int p, q;
    // p = generate_prime();
    // q = generate_prime();
    cout << "Enter p and q space separated: " << endl;
    cin >> p >> q;
    cout << "p: " << p << endl;
    cout << "q: " << q << endl;
    n = p * q;
    int phi_n = (p - 1) * (q - 1);

    e = 2;
    while (gcd(e, phi_n) != 1)
    {
        e++;
    }

    d = 0;
    while (((d * e) % phi_n) != 1)
    {
        // cout<<d<<endl;
        d++;
    }
    cout << "Encryption Key is: " << e << endl;
    cout << "Decryption key is: " << d << endl;
}

int encrypt(int plaintext, int e, int n)
{
    int ciphertext = 1;
    for (int i = 0; i < e; i++)
    {
        ciphertext = (ciphertext * plaintext) % n;
    }
    return ciphertext;
}

int decrypt(int ciphertext, int d, int n)
{
    int plaintext = 1;
    for (int i = 0; i < d; i++)
    {
        plaintext = (plaintext * ciphertext) % n;
    }
    return plaintext;
}

int main()
{
    long long e, d, n;
    srand(time(NULL));
    generate_keys(e, d, n);

    int plaintext;
    cout << "Enter Plain Text: " << endl;
    cin >> plaintext;
    int ciphertext = encrypt(plaintext, e, n);
    cout << "Ciphertext: " << ciphertext << endl;
    int decrypted_plaintext = decrypt(ciphertext, d, n);
    cout << "Decrypted Plaintext: " << decrypted_plaintext << endl;

    return 0;
}
