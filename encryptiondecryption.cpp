#include <iostream>
#include <cctype>
#include <vector>

using namespace std;

string encryptCaesar(string text, int shift) {
    string result = "";

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            result += char((text[i] - base + shift) % 26 + base);
        } else {
            result += text[i];
        }
    }
    return result;
}

string decryptCaesar(string text, int shift) {
    return encryptCaesar(text, 26 - shift); // Decryption is essentially encryption with the opposite shift
}

string encryptRowColumnTransposition(string text, int rows, int cols) {
    // Padding if needed
    while (text.length() % (rows * cols) != 0) {
        text += 'X';
    }

    vector<vector<char>> matrix(rows, vector<char>(cols));

    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = text[k++];
        }
    }

    string result = "";

    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            result += matrix[i][j];
        }
    }

    return result;
}

string decryptRowColumnTransposition(string text, int rows, int cols) {
    return encryptRowColumnTransposition(text, cols, rows); // Swap rows and columns for decryption
}

int main() {
    int choice;
    int symChoice;
    string symKey;

    do {

        cout << "Symmetric Encryption Menu:" << endl;
        cout << "1. Enter Symmetric Key" << endl;
        cout << "2. Enter Asymmetric Key" << endl;
        cout << "Enter your choice: ";
        cin >> symChoice;

        switch (symchoice)
        // Display main menu options
        cout << "Main Menu:" << endl;
        cout << "1. Caesar Cipher" << endl;
        cout << "2. Row-Column Transposition" << endl;
        cout << "3. Option 3" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        // Get user input
        cin >> choice;

        switch (choice) {
            case 1: // Caesar Cipher
                {
                    int caesarChoice;
                    cout << "Caesar Cipher Menu:" << endl;
                    cout << "1. Encrypt" << endl;
                    cout << "2. Decrypt" << endl;
                    cout << "Enter your choice: ";
                    cin >> caesarChoice;

                    if (caesarChoice == 1) {
                        string text;
                        int shift;
                        cout << "Enter the text to encrypt: ";
                        cin.ignore();
                        getline(cin, text);
                        cout << "Enter the shift value: ";
                        cin >> shift;
                        cout << "Text : " << text << endl;
                        cout << "Shift: " << shift << endl;
                        cout << "Encrypted: " << encryptCaesar(text, shift) << endl;
                    } else if (caesarChoice == 2) {
                        string text;
                        int shift;
                        cout << "Enter the text to decrypt: ";
                        cin.ignore();
                        getline(cin, text);
                        cout << "Enter the shift value: ";
                        cin >> shift;
                        cout << "Text : " << text << endl;
                        cout << "Shift: " << shift << endl;
                        cout << "Decrypted: " << decryptCaesar(text, shift) << endl;
                    } else {
                        cout << "Invalid choice. Please enter 1 or 2." << endl;
                    }
                }
                break;

            case 2: // Row-Column Transposition
                {
                    int transpositionChoice;
                    cout << "Row-Column Transposition Menu:" << endl;
                    cout << "1. Encrypt" << endl;
                    cout << "2. Decrypt" << endl;
                    cout << "Enter your choice: ";
                    cin >> transpositionChoice;

                    if (transpositionChoice == 1) {
                        string text;
                        int rows, cols;
                        cout << "Enter the text to encrypt: ";
                        cin.ignore();
                        getline(cin, text);
                        cout << "Enter the number of rows: ";
                        cin >> rows;
                        cout << "Enter the number of columns: ";
                        cin >> cols;
                        cout << "Text : " << text << endl;
                        cout << "Encrypted: " << encryptRowColumnTransposition(text, rows, cols) << endl;
                    } else if (transpositionChoice == 2) {
                        string text;
                        int rows, cols;
                        cout << "Enter the text to decrypt: ";
                        cin.ignore();
                        getline(cin, text);
                        cout << "Enter the number of rows: ";
                        cin >> rows;
                        cout << "Enter the number of columns: ";
                        cin >> cols;
                        cout << "Text : " << text << endl;
                        cout << "Decrypted: " << decryptRowColumnTransposition(text, rows, cols) << endl;
                    } else {
                        cout << "Invalid choice. Please enter 1 or 2." << endl;
                    }
                }
                break;

            case 3:
                cout << "You selected Option 3." << endl;
                // Add code for Option 3
                break;
            case 4:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }

    } while (choice != 4);

    return 0;
}

