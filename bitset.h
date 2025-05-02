#define WORD_TYPE int
#define WORD_SIZE (sizeof(WORD_TYPE) * 8)

void printBitsetFromWord(WORD_TYPE word);

typedef struct 
{
    WORD_TYPE *packed_data;     // T: pointer to the memory are that is currently used to store bits
    unsigned int size;                   // T: number of bits that are currently stored in bitset
    unsigned int capacity;               // T: number of words of type WORD_TYPE that are occupied in memory to store bits
} Bitset;

// T: This macro alloc memory on heap to store a certain number of bits on heap
#define create_bitset()
// T: This macro use memory pointed from "pointer" of size "size" to store bits in it
// T: NOTE this is useful if you want to allocate on stack your bitset 
#define create_bitset_from_mem(bitset, pointer, size) bitset.packed_data = pointer; bitset.capacity = size; 

#define _word_index(i) i / WORD_SIZE
#define _internal_index(i) i % WORD_SIZE  
#define set_true(bitset, i) bitset.packed_data[_word_index(i)] |= 1 << (_internal_index(i)) 
#define set_false(bitset, i) bitset.packed_data[_word_index(i)] &= ~(1 << (_internal_index(i))) 
#define get(bitset, i) bitset.packed_data[_word_index(i)] & 1 << (_internal_index(i))

