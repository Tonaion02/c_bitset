//==================================================================================================================================
//----------------------------------------------------------------------------------------------------------------------------------
// BITSET
//----------------------------------------------------------------------------------------------------------------------------------
// T: This is a simple implementation of a bitset.
// T: This implementation use a "word"(a type between integer, char...) to allocate memory and pack as any bit
// is possible in a word. The default type that is setted to be used like word is char.
// You can re-define the type that is used for the type of the word, defining the macro "WORD_TYPE" before
// to include bitset.h. 
// 
// 
// T: In this implementation is possible to allocate the entire bitset like a single piece of contigous memory.
// Even if we have a buffer in the struct of variable lenght, with a trick is possible to allocate the memory
// like a single block of memory.
//
// 
// T: We can decide if we want to allocate memory on the stack or in the heap using different methods or macros.
// T: refer to examples that are contained in the README.md to understand how.
// The basic implementation allocate memory on the heap using the malloc function.
// In this implementation is also possible to decide what is the function that is used to allocate
// memory on the heap. We can redefine the macros: _allocate_mem, _free_mem.  
//
//
// TO-DO:
// - Add a macro(or at least an example) that brings you possibility to handle allocation of memory outside of this function
// - Probably there is a great problem with the fact that i can't use the numbers that i am using
// - Add some operations:
//      - Give the possibility to enlarge the bitset, so to extend the bitset out of the current size.
//      - Create a macro to copy an entire bitset from an existing bitset.
//      - Create a macro to allocate the bitset on the stack.
//==================================================================================================================================
#ifndef _BITSET
#define _BITSET
#include "custom_assert.h"



// T: NOTE I Inserted the guard on WORD_TYPE. In this way, if WORD_TYPE is already defined by the user outside 
// this file, we don't ovverride the choice of the user. 
#ifndef WORD_TYPE
#define WORD_TYPE char
#endif



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



// T: size of the word used in *bit*
#define WORD_SIZE (sizeof(WORD_TYPE) * 8)



// T: WARNING private macro
// T: This macro is used to access the word where the i-th bit is contained
#define _word_index(i) i / WORD_SIZE
// T: WARNING private macro
// T: This macro is used to access the correct position of a WORD in the bitset
#define _internal_index(i) i % WORD_SIZE
// T: Macros used to handle memory (START)
// T: These macros are used to specify which functions are used to allocate and free memory on the heap.
// It is useful to easily adapt this implementation of bitset to all platform where we don't have an
// implemenentation of malloc and free.
// T: WARNING private macro
#define _allocate_mem malloc
// T: WARNING private macro
#define _free_mem free
// T: Macros used to handle memory (END)

// T: Default allocation of a bitset is made on the heap.
// T: TODO try to fix the fact that the allocation of biset is made only on the heap. Give the possibility to chose where we want to allocate the bitset.
#define create_bitset(bitset_p, _size)                                              \
    {                                                                               \
        int t = _size / WORD_SIZE + (int)((_size % WORD_SIZE) >= 1);                \
        bitset_p = (Bitset*) _allocate_mem(sizeof(Bitset) + t * sizeof(WORD_TYPE)); \
        bitset_p->size = _size;                                                     \
        bitset_p->capacity = t;                                                     \
    } 
                                   
#define free_bitset(bitset_p)   \
    _free_mem(bitset_p);

#define set_true(bitset_p, i)                                                                   \
    ASSERT(i < bitset_p->size)                                                                  \
    bitset_p->packed_data[_word_index((i))] |= 1 << (WORD_SIZE - 1 - _internal_index((i)));

#define set_false(bitset_p, i)                                                                  \
    ASSERT(i < bitset_p->size)                                                                  \
    bitset_p->packed_data[_word_index((i))] &= ~(1 << (WORD_SIZE - 1 - _internal_index((i))));

#define set_bit(bitset_p, i, bit)           \
    ASSERT(i < bitset_p->size)                                                      \
    bitset_p->packed_data[_word_index((i))] = (bitset_p->packed_data[_word_index((i))] & ~((!bit) << (WORD_SIZE - 1 - _internal_index((i))))  ) | ((bit) << (WORD_SIZE - 1 - _internal_index((i))));

// T: This macro doesn't end with ";" because the result of the operation computed in this macro is probably used in other expresions.
// For example in assignment expressions. 
#define get_bit(bitset, i)                                                                      \
    ASSERT(i < bitset_p->size)                                                                  \
    bitset->packed_data[_word_index((i))] & (1 << (WORD_SIZE - 1 - _internal_index((i))))

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

// T: NOTE this operation assume that bitset_1 and bitset_2 have the same size
#define and(bitset_1, bitset_2)                                                                  \
    {                                                                                            \
        ASSERT(bitset_1->size == bitset_2->size)                                                 \
        for(int i = 0; i < bitset_1->capacity; i++)                                              \
        {                                                                                        \
            bitset_1->packed_data[i] &= bitset_2->packed_data[i];                                \
        }                                                                                        \
    }

// T: NOTE this operation assume that biset_1 and bitset_2 have the same size
#define or(bitset_1, bitset_2)                                                                          \
    {   \
        ASSERT(bitset_1->size == bitset_2->size) \
        for(int i = 0; i < bitset_1->capacity; i++) \
        {   \
            bitset_1->packed_data[i] |= bitset_2->packed_data[i];   \
        }   \
    }

#define not(bitset_p)                                                                           \
    {\
        for(int i = 0; i < bitset_p->capacity; i++)\
        {\
            bitset_p->packed_data[i] = ~bitset_p->packed_data[i];\
        }\
    } 

#define print_word_bitset(word) \
    { \
        int i; \
        for(i = (sizeof(WORD_TYPE) * 8) -1; i >= 0; i--) \
        { \
        int b = word & (1 << i);   \
        printf("%d", (int)(b != 0)); \
        } \
    } 

#define print_bitset(bitset_p) \
    { \
        for(int i = 0; i < bitset_p->capacity; i++) \
        { \
            for(int j = WORD_SIZE -1; j >= 0; j--) \
            {   \
                if(i * WORD_SIZE + j < bitset_p->size) \
                { \
                    int b = bitset_p->packed_data[i] & (1 << _internal_index(j)); \
                    printf("%d", (int)(b != 0));    \
                } \
            } \
            printf("\n"); \
        } \
    }
//==================================================================================================================================
// BITSET
//==================================================================================================================================
#endif