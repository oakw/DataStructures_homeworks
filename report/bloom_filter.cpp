// Run with C++20 or newer
#include "hashing.cpp"
#include "bit_array.cpp"

using namespace std;

// This tutorial heavily relies and even copies some snippets from 
// https://www.geeksforgeeks.org/bloom-filters-introduction-and-python-implementation/
#undef ARR_SIZE
#define ARR_SIZE 100

// Just a utility function to print red text
void print_red(string s) {
    printf("\033[1;31m%s\033[0m\n", s.c_str());
}

// Just a utility function to print green text
void print_green(string s) {
    printf("\033[1;32m%s\033[0m\n", s.c_str());
}

void print_hashes(string s) {
    printf("hash1(%s): %d\n", s.c_str(), h1(s, ARR_SIZE));
    printf("hash2(%s): %d\n", s.c_str(), h2(s, ARR_SIZE));
    printf("hash3(%s): %d\n", s.c_str(), h3(s, ARR_SIZE));
    printf("hash4(%s): %d\n", s.c_str(), h4(s, ARR_SIZE));
}

// Look if a hash representing the string is present in the bit array
bool lookup(BitArray* bitArray, string s) { 
    if (
        bitArray->get_bit(h1(s, ARR_SIZE)) &&
        bitArray->get_bit(h2(s, ARR_SIZE)) &&
        bitArray->get_bit(h3(s, ARR_SIZE)) &&
        bitArray->get_bit(h4(s, ARR_SIZE))
    )
        return true; 
    else
        return false; 
} 

// Record the string's hash in the bit array
void insert(BitArray* bitArray, string s) { 
    if (lookup(bitArray, s)) 
        cout << s << " is probably already present" << endl; 

    else { 
        bitArray->set_bit(h1(s, ARR_SIZE)); 
        bitArray->set_bit(h2(s, ARR_SIZE)); 
        bitArray->set_bit(h3(s, ARR_SIZE)); 
        bitArray->set_bit(h4(s, ARR_SIZE)); 
  
        cout << s << " inserted" << endl; 
    } 
} 


int main() {
    BitArray bitArray;
    printf("bit 0: %d\n", bitArray.get_bit(0));
    bitArray.set_bit(0);
    printf("bit 0: %d\n", bitArray.get_bit(0));
    bitArray.clear_bit(0);
    printf("bit 0: %d\n", bitArray.get_bit(0));


    // // printf("hash1(hello): %d\n", h1("hello", ARR_SIZE));
    print_hashes("hello");
    printf("\n");
    print_hashes("world");
    printf("\n");

    string sarray[33] 
        = { "abound",   "abounds",       "abundance", 
            "abundant", "accessible",    "bloom", 
            "blossom",  "bolster",       "bonny", 
            "bonus",    "bonuses",       "coherent", 
            "cohesive", "colorful",      "comely", 
            "comfort",  "gems",          "generosity", 
            "generous", "generously",    "genial", 
            "bluff",    "cheater",       "hate", 
            "blame",      "humanity",      "alphabet", 
            "hurt",     "nuke",          "gloomy", 
            "facebook", "instagram", "twitter" }; 

    for (int i = 0; i < 33; i++)
        insert(&bitArray, sarray[i]);


    string notPresentInArray[15] 
        = { "car", "bike", "scooter", "bus", "train", 
            "flight", "helicopter", "boat", "ship", 
            "submarine", "rocket", "satellite", "ufo", 
            "alien", "martian" };

    for (int i = 0; i < 15; i++) {
        if (lookup(&bitArray, notPresentInArray[i]))
            print_green(format("{} seems present in the bit array (just a coincidence\?\?)", notPresentInArray[i]));

        else
            print_red(format("{} not present in the bit array!", notPresentInArray[i]));
    }

    for (int i = 0; i < 33; i++) {
        if (lookup(&bitArray, sarray[i]))
            print_green(format("{} is probably present in the bit array", sarray[i]));

        else {
            print_red(format("{} is not present in the bit array. This is unexpected.", sarray[i]));
            return 1;
        }
    }

    return 0;
}