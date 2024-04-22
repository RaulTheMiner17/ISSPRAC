
#include <iostream>
#include <cmath>
using namespace std;

// Function to check if a number is prime or not
bool isPrime(int n) {
   if (n <= 1) {
       return false;
   }
   for (int i = 2; i <= sqrt(n); i++) {
       if (n % i == 0) {
           return false;
       }
   }
   return true;
}

// Function to find GCD of two numbers
int gcd(int a, int b) {
   if (b == 0) {
       return a;
   }
   return gcd(b, a % b);
}

// Function to perform modular exponentiation
int modPow(int base, int exponent, int modulus) {
   int result = 1;
   base = base % modulus;
   while (exponent > 0) {
       if (exponent % 2 == 1) {
           result = (result * base) % modulus;
       }
       base = (base * base) % modulus;
       exponent = exponent / 2;
   }
   return result;
}

int main() {
   // Step 1: Choose two prime numbers
   int p = 17, q = 11;

   // Step 2: Compute n and phi
   int n = p * q;
   int phi = (p - 1) * (q - 1);

   // Step 3: Choose an integer e such that 1 < e < phi and gcd(e, phi) = 1
   int e = 2;
   while (e < phi) {
       if (gcd(e, phi) == 1) {
           break;
       }
       e++;
   }

   // Step 4: Compute the secret key d
   int d = 1;
   while ((d * e) % phi != 1) {
       d++;
   }

   // Step 5: Print the public and private keys
   cout << "Public key: {" << e << ", " << n << "}" << endl;
   cout << "Private key: {" << d << ", " << n << "}" << endl;

   // Step 6: Encrypt the message
   string message = "hello";
   int encrypted[message.length()];
   for (int i = 0; i < message.length(); i++) {
       int m = message[i];
       int c = modPow(m, e, n);
       encrypted[i] = c;
   }

   // Step 7: Decrypt the message
   string decrypted;
   for (int i = 0; i < message.length(); i++) {
       int c = encrypted[i];
       int m = modPow(c, d, n);
       decrypted += static_cast<char>(m);
   }

   // Step 8: Print the encrypted and decrypted messages
   cout << "Encrypted message: ";
   for (int i = 0; i < message.length(); i++) {
       cout << encrypted[i] << " ";
   }
   cout << endl;
   cout << "Decrypted message: " << decrypted << endl;

   return 0;
}
