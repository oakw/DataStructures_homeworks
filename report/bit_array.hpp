#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#define ARR_SIZE 1000

#include <iostream>
#include <bitset>

class BitArray {
    uint32_t data[ARR_SIZE / 32 + 1];
    
    inline int bindex(int i);
    inline int boffset(int i);

    public:
        BitArray();
        void set_bit(int i);
        void clear_bit(int i);
        int get_bit(int i);
};

#endif