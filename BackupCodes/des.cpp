

#include <iostream>
#include <bitset>
#include <string>
using namespace std;

bitset<56> bitReduction(const bitset<64>& key) {
    bitset<56> reducedKey;
    int j = 0;
    for (int i = 0; i < 64; ++i) {
        if ((i + 1) % 8 != 0) {
            reducedKey[j++] = key[i];
        }
    }
    return reducedKey;
}

bitset<64> leftShift2(const bitset<64>& data) {
    return (data << 2) | (data >> (64 - 2));
}

bitset<28> leftShift(const bitset<28>& keyPart, int round) {
    int shiftAmount = (round == 1 || round == 9 || round == 16) ? 1 : 2;
    return (keyPart << shiftAmount) | (keyPart >> (28 - shiftAmount));
}

int main() {
    // Get user input for data string
    string dataInput;
    cout << "Enter 64-bit Data String: ";
    cin >> dataInput;
    bitset<64> dataString(dataInput);

    string firstPart = dataInput.substr(0, 32);
    string secondPart = dataInput.substr(32, 64);

    cout << "L0 bits of Data: " << firstPart << endl;
    cout << "R0 bits of Data: " << secondPart << endl;

   /* bitset<48> ExpandedR0(secondPart) {
    int a=0;
    for(int e=0,)
    }
*/

    // Get user input for key string
    string keyInput;
    cout << "Enter 64-bit Key String: ";
    cin >> keyInput;
    bitset<64> keyString(keyInput);

    // Perform bit reduction on the key
    bitset<56> reducedKey = bitReduction(keyString);

    // Split the reduced key into left and right parts
    bitset<28> leftPart(reducedKey.to_string().substr(0, 28));
    bitset<28> rightPart(reducedKey.to_string().substr(28, 28));

    // Print original input data, shifted input data, input key, and reduced input key
    cout << "Original Input Data: " << dataString << endl;
    cout << "Shifted Input Data: " << leftShift2(dataString) << endl;
    cout << "Input Key: " << keyString << endl;
    cout << "Reduced Input Key: " << reducedKey << endl;

    // Print left and right parts of the reduced key
    cout << "Left Part of Reduced Key: " << leftPart << endl;
    cout << "Right Part of Reduced Key: " << rightPart << endl;

    // Perform left shift on left and right parts based on round
    for (int round = 1; round <= 16; ++round) {
        // Shift left and right parts
        leftPart = leftShift(leftPart, round);
        rightPart = leftShift(rightPart, round);

        // Print shifted left and right parts
        cout << "Round " << round << " Shifted Left Part: " << leftPart << endl;
        cout << "Round " << round << " Shifted Right Part: " << rightPart << endl;

        if(round==0){
            cout<< round<<"ROUND 1 "<< endl;
        }

        // Form new key by adding shifted left and right parts of previous round
        bitset<56> newKey = (leftPart.to_ullong() << 28) | rightPart.to_ullong();

        // Print new key formed
        cout << "Round " << round << " New Key Formed: " << newKey << endl;

        // Divide the new key into left and right parts for the next round
        //leftPart = newKey.to_string().substr(0, 28);
        //rightPart = newKey.to_string().substr(28, 28);
    }

    return 0;
}
