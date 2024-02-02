// Martins_Prokuratovs_221RDB473
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


const int MAX_VALUE = 50;
const int MIN_VALUE = 1;

int main() {
    int i;
    vector<int> numbers, missingNumbers;
    ifstream numberStream ("missing_2_numbers.txt");

    // Read stream of file contents and save numbers of it
    if ( numberStream.is_open() ) {
        while ( numberStream >> i ) {
            numbers.insert(numbers.begin(), i);
        }
    }

    // Generate all possible numbers
    for (int i = MIN_VALUE; i <= MAX_VALUE; i++) {
        // Borrowed the idea from here: https://stackoverflow.com/a/571405
        if (find(numbers.begin(), numbers.end(), i) == numbers.end()) {
            // If number not in file, mark as missing
            missingNumbers.insert(missingNumbers.begin(), i);
        }
    }


    printf("Missing numbers: \n");
    for (int i: missingNumbers) {
        cout << i << '\n';
    }
}