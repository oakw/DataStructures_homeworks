// Martins_Prokuratovs_221RDB473
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Compares two intervals according to starting times. 
bool compareByAbsoluteDesc(int i, int j) { 
    return abs(i) > abs(j); 
} 

int main() {
    int i = 0;
    vector<int> numbers;
    ifstream numberStream ("numbers_-50_50_20.txt");

    // Put all numbers from a file in the vector.
    if ( numberStream.is_open() ) {
        while ( numberStream >> i ) {
            numbers.insert(numbers.begin(), i);
        }
    }

    // Sort it in a way that largest numbers by modulus are at the beginning
    sort(numbers.begin(), numbers.end(), compareByAbsoluteDesc);

    // There are very few numbers
    if (numbers.size() <= 2) {
        if (numbers.size() == 1)
            cout << numbers[0];

        else if (numbers.empty())
            cout << 0;

        else
            cout << numbers[0] * numbers[1];

        return 0;
    }

    // Let's try to be efficient here.
    // There are only three cases possible now, since we also have to deal with negative numbers
    //  - first and second is both either positive or negative. Then their product will be the largest
    //  - first > 0, and second < 0, then largest product:
    //      - if third >= 0, then first * third
    //      - if third < 0, then second * third
    //  - first < 0, and second > 0, then largest product:
    //      - if third >= 0, then second * third
    //      - if third < 0, then first * third
    if (numbers[0] > 0 && numbers[1] > 0 || (numbers[0] < 0 && numbers[1] < 0) || numbers.size() <= 2) {
        cout << numbers[0] * numbers[1];

    } else if (numbers[0] > 0 && numbers[1] < 0) {
        if (numbers[2] >= 0) cout << numbers[0] * numbers[2];
        else cout << numbers[1] * numbers[2];

    } else {
        if (numbers[2] >= 0) cout << numbers[1] * numbers[2];
        else cout << numbers[0] * numbers[2];
    }
    
    return 0;
}