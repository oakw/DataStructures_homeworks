// Week 2 Homework 2
// Martins P
#include <iostream>


const char charCodes[26][9] = {
    "Alpha", "Bravo", "Charlie",
    "Delta", "Echo", "Foxtrot",
    "Golf", "Hotel", "India",
    "Juliett", "Kilo", "Lima",
    "Mike", "November", "Oscar",
    "Papa", "Quebec", "Romeo",
    "Sierra", "Tango", "Uniform",
    "Victor", "Whiskey", "Xray",
    "Yankee", "Zulu"
};
const char numCodes[10][6] = {
    "Zero", "One", "Two", "Three",
    "Four", "Five", "Six",
    "Seven", "Eight", "Nine"
};


int main() {
    char input;
    
    printf("Input an uppercase letter or digit: ");
    std::cin >> input;

    if (input >= 'A' && input <= 'Z') {
        // User inputted a letter
        printf("%s", charCodes[input - 'A']);

    } else if (input >= '0' && input <= '9') {
        // User inputted a digit
        printf("%s", numCodes[input - '0']);

    } else {
        printf("Not Recognized");
    }

    return 0;
}