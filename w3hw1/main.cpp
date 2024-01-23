// Week 3 Homework 1
// Martins P
#include <iostream>
#include <cmath>

using namespace std;


bool isPrime(int num) {
    if (num <= 1) {
        return false;
    }

    // Checks if any of integers smaller than the root of the number divides it
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) {
            // Divides. Is NOT a prime number
            return false;
        }
    }

    // Nothing to divide by. Is a prime number
    return true;
}

int main() {
    cout << boolalpha << 
        isPrime(1000001) << " " <<
        isPrime(1000021) << " " <<
        isPrime(1000037) << endl;
}
