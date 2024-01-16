// Week 2 Homework 1
// Martins P
#include <iostream>
#include <algorithm>


int main() {
    const int NUMBER_COUNT = 3;
    int numbers[NUMBER_COUNT - 1];
    
    for (int i = 0; i < NUMBER_COUNT; i++) {
        printf("Enter number %d: ", i + 1);
        std::cin >> numbers[i];
    }

    // Sort numbers in ascending order
    std::sort(numbers, numbers + NUMBER_COUNT);

    printf("Three numbers in ascending order: %d, %d, %d", numbers[0], numbers[1], numbers[2]);
    return 0;
}