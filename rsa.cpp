#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

int gcd(int a, int b) {
    int remainder;
    int flag = 0;

    while (flag == 0) {
        if (a != 0 && b != 0) {
            remainder = a % b;

            a = b;
            b = remainder;
        } else {
            if (a == 0) {
                return b;
                flag = 1;
            } else if (b == 0) {
                return a;
                flag = 1;
            }
        }
    }
}

int main() {
    double p, q, n, phin, d, e = 0, k = 2;
    string message, encryptedText = "";
    int asciiValue = 0, encryptedTextNumber = 0;

    cout << "Enter the value of p: ";
    cin >> p;

    cout << "Enter the value of q: ";
    cin >> q;

    n = p * q;

    cout << "\nValue of n: " << n;

    phin = (p - 1) * (q - 1);

    cout << "\nValue of phi(n): " << phin;

    e = gcd(p, q);

    cout <<"\nValue of e: " << e;

    d = ((k * phin) + 1) / e;

    cout << "\nValue of d: " << d;

    cout << "\n\nEnter message: ";
    cin >> message;

    for (char ch : message) {
        asciiValue = (int)ch;
        encryptedText.append(to_string(asciiValue));
    }

     encryptedTextNumber = stoi(encryptedText);


}

