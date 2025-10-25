#ifndef _BITSET
#define _BITSET
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
// - Give possibility to allocate this struct on the stack
// - Check if macro WORD_SIZE is a problem
// - Check if there are problem in re-defining the macro WORD_TYPE
// - Probably there is a great problem with the fact that i can't use the numbers that i am using
// - Probably we don't need a .c, so we don't use it
// - Add some assert to check some conditions in debug mode(controlled by some macro)
//==================================================================================================================================

// T: NOTE I Inserted the guard on WORD_TYPE. In this way, if WORD_TYPE is already defined by the user outside 
// this file, we don't ovverride the choice of the user. 
#ifndef WORD_TYPE
#define WORD_TYPE char
#endif
// T: size of the word used in *bit*
#define WORD_SIZE (sizeof(WORD_TYPE) * 8)



typedef struct 
{
    unsigned int size;              // T: number of bits that are currently stored in bitset
    unsigned int capacity;          // T: number of words of type WORD_TYPE that are occupied in memory to store bits
    // T: This is a specific manner to specify a pointer in C.
    // T: Is is useful to allocate the entier bitset like a single piece of memory even if the buffer packed_data has a
    // variable length.
    // We can directly allocate memory for the entire bitset in this way(capacity is the number of words to allocate
    // to store the bit that we need to store):
    // Bitset *pointer = (Bitset*)malloc(sizeof(Bitset) + sizeof(WORD_TYPE) * size));
    // In this way packed_data start directly from the address next to capacity.
    // T: How we already sayed, the advantage to use this trick is that now the allocation of the Bitset is entirely contigous.
    WORD_TYPE packed_data[0];       
} Bitset;



// T: WARNING private macro
// T: This macro is used to access the  
#define _word_index(i) i / WORD_SIZE
#define _internal_index(i) i % WORD_SIZE  

// T: Default allocation of a bitset is made on the heap.
// T: TODO try to fix the fact that the allocation of biset is made only on the heap. Give the possibility to chose where we want to allocate the bitset.
#define create_bitset(bitset_p, _size)                                              \
    {                                                                               \
        int t = _size / WORD_SIZE + (int)((_size % WORD_SIZE) >= 1);                \
        bitset_p = (Bitset*)malloc(sizeof(Bitset) + t * sizeof(WORD_TYPE));         \
        bitset_p->size = _size;                                                     \
        bitset_p->capacity = t;                                                     \
    } 
                                                      
#define free_bitset(bitset_p)   \
    free(bitset_p);             \
    bitset_p->size = 0;         \
    bitset_p->capacity = 0;

#define set_true(bitset_p, i) bitset_p->packed_data[_word_index((i))] |= 1 << (WORD_SIZE - 1 - _internal_index((i)));
#define set_false(bitset_p, i) bitset_p->packed_data[_word_index((i))] &= ~(1 << (WORD_SIZE - 1 - _internal_index((i))));
// T: This macro doesn't end with ";" because the result of the operation computed in this macro is probably used in other expresions.
// For example in assignment expressions. 
#define get(bitset, i) bitset->packed_data[_word_index((i))] & (1 << (WORD_SIZE - 1 - _internal_index((i))))

#define all_true(bitset_p)                              \
    {                                                   \
        for(int i = 0; i < bitset_p->capacity; i++)     \
        {                                               \
            bitset_p->packed_data[i] |= ~0;             \
        }                                               \
    }
#define all_false(bitset_p)                             \
    {                                                   \
        for(int i = 0; i < bitset_p->capacity; i++)     \
        {                                               \
            bitset_p->packed_data[i] &= 0;              \
        }                                               \
    }

void print_word_bitset(WORD_TYPE word);
void print_bitset(Bitset *bitset_p);
//==================================================================================================================================
// BITSET
//==================================================================================================================================
#endif