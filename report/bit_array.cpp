#include "bit_array.hpp"

// Based on https://stackoverflow.com/a/2633584

BitArray::BitArray() {
    for (int i = 0; i < ARR_SIZE / 32 + 1; i++)
        this->data[i] = 0; // Set all values to zero
}

inline int BitArray::bindex(int i) { 
    return i / (sizeof(uint32_t) * 8); 
}

inline int BitArray::boffset(int i) { 
    return i % (sizeof(uint32_t) * 8); 
}

// Set i-th bit to one
void BitArray::set_bit(int i) {
    this->data[bindex(i)] |= 1 << boffset(i); 
}

// Set i-th bit to zero
void BitArray::clear_bit(int i) { 
    this->data[bindex(i)] &= ~(1 << boffset(i)); 
}

// Get the value of the i-th bit
int BitArray::get_bit(int i) {
    return this->data[bindex(i)] & (1 << boffset(i)); 
}
