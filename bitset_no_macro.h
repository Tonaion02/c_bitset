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
// - Add the missing operations: print_word_bitset
// - Add the possibility to extend the current bitset, like an std::vector
// - Add an operation to copy bitset
// - Add give the user more freedom for allocation of memory: possibility to allocate on the stack or to make a total custom allocation
// - Give to the user the possibility to allocate in a single piece of memory size, capacity and packed_data, or 
// to allocate (size, capacity) and then packed_data
// - Re-write the doc
// Things to check:
// - Check if prints only the bits for size and not the entire capacity
// - Check if all the ASSERT works
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
    bitset->packed_data[_word_index(i)] |= (1 << (_internal_index(i)));
}

void set_false(CBitSet* bitset, uint32_t i)
{
    ASSERT(i < bitset->size)
    bitset->packed_data[_word_index(i)] &= ~(1 << (_internal_index(i)));
}

// T: TODO Think if it is the best type to return
uint8_t get_bit(CBitSet* bitset, uint32_t i)
{
    ASSERT(i < bitset->size)
    return bitset->packed_data[_word_index(i)] & (1 << _internal_index(i));
}

// T: TODO Think if it is the best type to represent a bit
void set_bit(CBitSet* bitset, uint32_t i, uint8_t bit)
{
    ASSERT(i < bitset->size)
    // T: It's necessary this assert, set_bit work only with bit = 0 or bit = 1.
    ASSERT(bit == 1 || bit == 0)
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

// T: TODO Think about the fact that probably it's useful to implement
// "and" and "or" operations even for bitset of different size.
// T: and method perform the an and bit a bit operation between the first bitset
// and the second bitset.
// T: The result of the and operation is stored in the first bitset, the second
// bitset isn't modified at all.
void and(CBitSet* bitset1, CBitSet* bitset2)
{
    ASSERT(bitset1->size == bitset2->size)
    for(uint32_t i = 0; i < _size_in_word(bitset1->size); i++)
    {
        bitset1->packed_data[i] &= bitset2->packed_data[i];
    }
}

void or(CBitSet* bitset1, CBitSet* bitset2)
{
    ASSERT(bitset1->size == bitset2->size)
    for(uint32_t i = 0; i < _size_in_word(bitset1->size); i++)
    {
        bitset1->packed_data[i] |= bitset2->packed_data[i];
    }    
}

void not(CBitSet* bitset)
{
    // T: OPT Probably it's not necessary to set negate even the bits that are out of size
    for(uint32_t i = 0; i < bitset->capacity; i++)
    {
        bitset->packed_data[i] = ~bitset->packed_data[i];
    }
}

void print_bitset(CBitSet* bitset)
{
    // T: NOTE Indexes i,j are handled deciding to go from 1..capacity or 1..WORD_SIZE,
    // even if the valid values goes from 0..(capacity-1) and 0..(WORD_SIZE-1) because
    // in this way I can define them like uint32_t and match with indexes the types
    // of capacity and size field of the bitset.
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
}

#endif