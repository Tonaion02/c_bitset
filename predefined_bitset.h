#ifndef __PREDEFINED_BITSET
#define __PREDEFINED_BITSET

#include <stdlib.h>

#define predefined_bitset(word_type, word_type_alias)   \
    typedef struct                 \
    {                              \
        unsigned int size;         \
        unsigned int capacity;     \
        word_type *packed_data;    \
    } word_type_alias##Bitset;     \
                                   \
    #define word_type##_create_bitset() 

predefined_bitset(int, i)
predefined_bitset(unsigned int, ui)
predefined_bitset(char, c)
predefined_bitset(unsigned char, uc)
#endif