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
// memory on the heap. You can do that redefining the macros: _allocate_mem, _free_mem.  
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


// T: TODO It's necessary to check if it is possible to remove this include from here.
#include <stdint.h> 
#include <stdlib.h>
#include <stdio.h>
#include "custom_assert.h"


// T: NOTE I Inserted the guard on WORD_TYPE. In this way, if WORD_TYPE is already defined by the user outside 
// this file, we don't ovverride the choice of the user. 
#ifndef WORD_TYPE
#define WORD_TYPE char
#endif

typedef struct 
{
    uint32_t size;              // T: number of bits that are currently stored in bitset
    uint32_t capacity;          // T: number of words of type WORD_TYPE that are occupied in memory to store bits
    WORD_TYPE packed_data[0];
} CBitSet;


// T: Size of the word in bit
#define WORD_SIZE (sizeof(WORD_TYPE) * 8)



#define _word_index(i) i / WORD_SIZE
#define _internal_index(i) i % WORD_SIZE
// T: TODO This macro is useful to get the number of words that are really used by the bitset
#define _size_in_word(size) (size / WORD_SIZE + (int)((size % WORD_SIZE) >= 1))

#define _allocate_mem malloc
#define _free_mem free

CBitSet* create_bitset(uint32_t _size)
{
    uint32_t capacity = _size_in_word(_size);
    CBitSet* p = (CBitSet*)_allocate_mem(sizeof(CBitSet) + sizeof(WORD_TYPE) * capacity);
    // CBitSet* p = (CBitSet*)calloc(1, sizeof(CBitSet) + sizeof(WORD_TYPE) * capacity);
    ASSERT(p != NULL)
    p->capacity = capacity;
    p->size = _size;

    return p;
}

void free_bitset(CBitSet* bitset)
{
    _free_mem(bitset);
}

void set_true(CBitSet* bitset, uint32_t i)
{
    ASSERT(i < bitset->size)
    // bitset->packed_data[_word_index(i)] |= (1 << (WORD_SIZE - 1 - _internal_index(i)));
    bitset->packed_data[_word_index(i)] |= (1 << (_internal_index(i)));
}

void set_false(CBitSet* bitset, uint32_t i)
{
    ASSERT(i < bitset->size)
    // bitset->packed_data[_word_index(i)] &= ~(1 << (WORD_SIZE - 1 - _internal_index(i)));
    bitset->packed_data[_word_index(i)] &= ~(1 << (_internal_index(i)));
}

void set_bit(CBitSet* bitset, uint32_t i, uint8_t bit)
{
    ASSERT(i < bitset->size)
    // T: It's necessary this assert, set_bit work only with bit = 0 or bit = 1.
    ASSERT(bit == 1 || bit == 0)
    // bitset->packed_data[_word_index(i)] |= (bit << (WORD_SIZE - 1 - _internal_index(i)));
    // bitset->packed_data[_word_index(i)] &= ~(bit << (WORD_SIZE - 1 - _internal_index(i)));
    bitset->packed_data[_word_index(i)] |= (bit << (_internal_index(i)));
    bitset->packed_data[_word_index(i)] &= ~(!bit << (_internal_index(i)));
}

void all_true(CBitSet* bitset)
{
    // T: OPT Probably I can optimize iterating on capacity
    for(uint32_t i = 0; i < bitset->capacity; i++)
    {
        bitset->packed_data[i] |= (WORD_TYPE)~0;
    }
}

void all_false(CBitSet* bitset)
{
    // T: OPT Probably I can optimize iterating on capacity
    for(uint32_t i = 0; i < bitset->capacity; i++)
    {
        bitset->packed_data[i] &= 0;
    }
}

// T: NOTE Possible problem, indexes must be signed integer, but capacity and size are unsigned 
void print_bitset(CBitSet* bitset)
{
    for(uint32_t i = bitset->capacity; i >= 1; i--)
    {
        for(uint32_t j = WORD_SIZE; j >=1; j--)
        {
            if((i-1) * WORD_SIZE + (j-1) < bitset->size)
            {
                int b = bitset->packed_data[i-1] & (1 << (j-1));
                printf("%d", (int)(b != 0));
            }
        }
        printf("\n");
    }

    // T: Printing in another order
    // for(uint32_t i = 0; i < bitset->capacity; i++)
    // {
    //     for(int32_t j = WORD_SIZE - 1; j >= 0; j--)
    //     {
    //         if(i * WORD_SIZE + j < bitset->size)
    //         {
    //             int b = bitset->packed_data[i] & (1 << j);
    //             printf("%d", (int)(b != 0));
    //         }
    //     }
    //     printf("\n");
    // }
}

#endif