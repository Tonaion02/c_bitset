#include <stdlib.h>





//==================================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------------
// BITSET
//----------------------------------------------------------------------------------------------------------------------------------
// This is a simple implementation of a bitset.
// This implementation use a "word"(a type between integer, char...) to allocate memory and pack as any bit
// is possible in a word. The default type that is setted to be used like word is int.
// You can re-define the type that is used for the type of the word, re-defining with a macro "WORD_TYPE"
//
//
//
// TO-DO:
// - Add a macro(or at least an example) that brings you possibility to handle allocation of memory outside of this function
// - Check if macro WORD_SIZE is a problem
// - Check if there are problem in re-defining the macro WORD_TYPE
//   Probably there is a great problem with the fact that i can't use the numbers that i am using
// - Mark all the macro that are private in some manner and report this in the comment
// - Probably we don't need a .c, so we don't use it
// - Add some assert to check some conditions in debug mode(controlled by some macro)
//==================================================================================================================================
#define WORD_TYPE int
// T: size of the word used in *bit*
// T: WARNING probably this macro is dangerous. It can easily become a problem because if someone re-define the WORD_TYPE,
// after the inclusion of the header, probably the WORD_SIZE is not re-computed
#define WORD_SIZE (sizeof(WORD_TYPE) * 8)



typedef struct 
{
    WORD_TYPE *packed_data;         // T: pointer to the memory are that is currently used to store bits
    unsigned int size;              // T: number of bits that are currently stored in bitset
    unsigned int capacity;          // T: number of words of type WORD_TYPE that are occupied in memory to store bits
} Bitset;



#define _word_index(i) i / WORD_SIZE
#define _internal_index(i) i % WORD_SIZE  



#define create_bitset(bitset, _size) bitset.size = _size; { int t = _size / WORD_SIZE + (int)((_size % WORD_SIZE) >= 1); bitset.capacity = t; bitset.packed_data = (WORD_TYPE*)malloc(t * sizeof(WORD_TYPE)); }  
#define free_bitset(bitset) free(bitset.packed_data); bitset.capacity = 0; bitset.size = 0

#define set_true(bitset, i) bitset.packed_data[_word_index(i)] |= 1 << (WORD_SIZE - 1 - _internal_index(i)) 
#define set_false(bitset, i) bitset.packed_data[_word_index(i)] &= ~(1 << (WORD_SIZE - 1 - _internal_index(i))) 
#define get(bitset, i) bitset.packed_data[_word_index(i)] & (1 << (WORD_SIZE - 1 - _internal_index(i)))
 
#define all_true(bitset) \
    { \
        for(int i = 0; i < bitset.capacity; i++)  \
        { \
            bitset.packed_data[i] |= ~0; \
        } \
    } \

#define all_false(bitset) \
    { \
        for(int i = 0; i < bitset.capacity; i++)  \
        { \
            bitset.packed_data[i] &= 0; \
        } \
    } \

void printBitsetFromWord(WORD_TYPE word);
void printBitset(Bitset bitset);
//==================================================================================================================================
// BITSET
//==================================================================================================================================