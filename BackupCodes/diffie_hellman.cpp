
#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int num)
{
    if (num <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= num; ++i)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

int generateRandomPrime(int range)
{
    int randomNum = rand() % range + 1;

    while (!isPrime(randomNum))
    {
        randomNum = rand() % range + 1;
    }

    return randomNum;
}

int power(int base, int exponent, int mod)
{
    int result = 1;
    base = base % mod;

    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            result = (result * base) % mod;
        }

        exponent = exponent >> 1;
        base = (base * base) % mod;
    }

    return result;
}

int main()
{
    srand(time(0));

    int p = generateRandomPrime(100);
    int g = rand() % 100 + 1;

    int a, b;
    cout << "Enter private key of A: ";
    cin >> a;

    cout << "Enter private key of B: ";
    cin >> b;

    int ga = power(g, a, p);
    int gb = power(g, b, p);

    cout << "p = " << p << endl;
    cout << "g = " << g << endl;
    cout << "ga = " << ga << endl;
    cout << "gb = " << gb << endl;

    int gab = power(ga, b, p);
    int gba = power(gb, a, p);

    cout << "gab = " << gab << endl;
    cout << "gba = " << gba << endl;

    return 0;
}

