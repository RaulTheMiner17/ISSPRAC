#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>

int main() {
    // Take user input for 64-bit data
    std::string dataInput;
    std::cout << "Enter a 64-bit data:       ";
    std::cin >> dataInput;

    // Check if the input is exactly 64 bits
    if (dataInput.length() != 64) {
        std::cerr << "Invalid input. Please enter a 64-bit data." << std::endl;
        return 1;
    }

    std::string firstPart = dataInput.substr(0, 32);
    std::string secondPart = dataInput.substr(32, 64);

    // Print the two 32-bit parts
    std::cout << "L0 32 bits:                " << firstPart << std::endl;
    std::cout << "R0 32 bits:                " << secondPart << std::endl;

    //  Shift data input to the left by 1
    std::rotate(dataInput.begin(), dataInput.begin() + 1, dataInput.end());

    // Print the shifted data
    std::cout << "Shifted Data to left by 1: " << dataInput << std::endl;

    // Take user input for 64-bit key
    std::string keyInput;
    std::cout << "Enter a 64-bit key:        ";
    std::cin >> keyInput;

    // Check if the input is exactly 64 bits
    if (keyInput.length() != 64) {
        std::cerr << "Invalid input. Please enter a 64-bit key." << std::endl;
        return 1;
    }

    //  Convert the key to 56-bit by removing the 8th bit
    std::bitset<64> originalKey(keyInput);
    originalKey.set(7, 0); // Set the 8th bit to 0
    std::bitset<56> reducedKey(originalKey.to_string().substr(0, 56));

    // Print the reduced key
    std::cout << "Reduced Key to 56-bit:     " << reducedKey << std::endl;

    //  Divide the reduced key into two parts L0 and R0, each 28 bits
    std::bitset<28> L0(reducedKey.to_string().substr(0, 28));
    std::bitset<28> R0(reducedKey.to_string().substr(28, 28));

    std::cout << "Left L0:                   " << L0 << std::endl;
    std::cout << "Right R0:                  " << R0 << std::endl;

    std::bitset<48> round1Key; // Define round 1 key outside the loop

    // Loop for 16 rounds
    for (int round = 1; round <= 16; ++round) {
        // Check if round is not 1,2, 9, or 16 for shifting L0 and R0 by 2
        if (round != 1 && round != 2 && round != 9 && round != 16) {
            // Shift L0 and R0 by 2
            L0 = ((L0 << 2) | (L0 >> 26)); // Circular left shift by 2
            R0 = ((R0 << 2) | (R0 >> 26)); // Circular left shift by 2
        } else {
            // For rounds 1,2, 9, and 16, shift by 1
            // Shift L0 and R0 by 1
            L0 = ((L0 << 1) | (L0 >> 27)); // Circular left shift by 1
            R0 = ((R0 << 1) | (R0 >> 27)); // Circular left shift by 1
        }

        // Combine L0 and R0 for the next round
        std::bitset<56> combinedKey;
        combinedKey |= std::bitset<56>(L0.to_string() + R0.to_string());

        // Print the combined key for the current round
        std::cout << "Round " << round << " Combined Key:      " << combinedKey << std::endl;

        // Take the result as input for the next round for 16 rounds
        if (round == 1) {
            // Define the permutation table for round 1
            int permutation_table[48] = {
                32,  1,  2,  3,  4,  5,
                 4,  5,  6,  7,  8,  9,
                 8,  9, 10, 11, 12, 13,
                12, 13, 14, 15, 16, 17,
                16, 17, 18, 19, 20, 21,
                20, 21, 22, 23, 24, 25,
                24, 25, 26, 27, 28, 29,
                28, 29, 30, 31, 32,  1
            };

            // Permute the combined key using the permutation table
            for (int i = 0; i < 48; ++i) {
                round1Key[i] = combinedKey[permutation_table[i] - 1];
            }

            // Print the round 1 key after permutation
            std::cout << "Round 1 Permuted Key:      " << round1Key << std::endl;
        }

        if (round == 16) {
            // Define the expansion permutation table
            int expansion_table[48] = {
                32,  1,  2,  3,  4,  5,
                 4,  5,  6,  7,  8,  9,
                 8,  9, 10, 11, 12, 13,
                12, 13, 14, 15, 16, 17,
                16, 17, 18, 19, 20, 21,
                20, 21, 22, 23, 24, 25,
                24, 25, 26, 27, 28, 29,
                28, 29, 30, 31, 32,  1
            };

            // Expand the secondPart 32-bit data to 48 bits using expansion permutation table
            std::bitset<48> expandedSecondPart;
            for (int i = 0; i < 48; ++i) {
                expandedSecondPart[i] = secondPart[32 + expansion_table[i]-1];
            }

            // Print the expanded secondPart
            std::cout << "Expanded R0:                " << expandedSecondPart << std::endl;

            // Convert firstPart, expandedSecondPart, and round1Key to std::bitset
            std::bitset<48> firstPartBits(firstPart);
            std::bitset<48> expandedSecondPartBits(expandedSecondPart);
            std::bitset<48> round1KeyBits(round1Key.to_string().substr(0, 48));

            // Perform XOR between L0 and R0
            std::bitset<48> firstXORResult = (firstPartBits ^ expandedSecondPartBits);

            // Perform XOR between firstXORResult and Combined Key 1
            std::bitset<48> finalXORResult = (firstXORResult ^ round1KeyBits);

            // Print the final result
            std::cout << "Final XOR Result [R1]:      " << finalXORResult << std::endl;
        }

    }

    return 0;
}


//1011100000101110000010111000001011100000101110000010111000001011
//0100011110101011101111010100101010010111101010111101100001111100
