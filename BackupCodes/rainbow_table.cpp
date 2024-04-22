
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void searchHash(const string& fileName, const string& passHash) {
    ifstream inFile(fileName);
    if (!inFile) {
        cerr << "Unable to open file";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        size_t pos = line.find(passHash);
        cout<<"line ",line<<endl;
        if (pos != string::npos) {
            cout << "Password found:" << endl;
            cout << line << endl;
            inFile.close();
            return;
        }
    }

    cout << "Password not found." << endl;
    inFile.close();
}

int main() {
    string fileName = "rainbow.txt";
    string passHash;

    cout << "Enter the password hash: ";
    cin >> passHash;

    searchHash(fileName, passHash);

    cout << "Press Enter to exit";
    cin.ignore();
    cin.get();
    return 0;
}

