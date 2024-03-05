#include <iostream>

using namespace std;


const bool PRINT_EVERY_STEP = false;

void collatz_recursive(int n, int *stepCount) {
    // Print the steps as instructed
    if (PRINT_EVERY_STEP)
        printf("    step %d: %d\n", *stepCount, n);

    if (n == 1) {
        // Stop when we reach 1
        return;
    }

    *stepCount += 1;

    // Compute as per the Collatz conjecture
    if (n % 2 == 0) {
        n = n / 2;
    } else {
        n = n * 3 + 1;
    }

    // Call this same function again
    collatz_recursive(n, stepCount);
}


// Wrapper for easy recursion initiating
void test_recursion(int n) {
    int stepCount = 0;
    collatz_recursive(n, &stepCount);
    printf("Steps for %d: %d\n", n, stepCount);
}


int main() {
    int n = 0;

    printf("Input a number: ");
    cin >> n;

    if (n <= 0) {
        printf("Invalid input\n");
        return 1;
    }

    test_recursion(n);

    // test_recursion(57);
    // test_recursion(289);
    // test_recursion(871);
    // test_recursion(62);
    // test_recursion(46);
    // test_recursion(163);

    return 0;
}