#include <stdio.h>
#include <stdlib.h>

#include "bitset.h"





int main()
{
    Bitset bitset;

    int n = 45;
    create_bitset(bitset, n);
 
    // T: print current capacity of Bitset
    // T: NOTE please note that the capacity of Bitset reppresent the number of "WORDS"
    // that are used to store the bits. The effective number of stored bits are size.
    printf("capacity of bitset: %d\n", bitset.capacity);

    printf("size of bitset: %d\n", bitset.size);
    
    // T: put all the bits of bitset to true
    all_true(bitset);
    printBitset(bitset);
    
    // T: put all bits of bitset to false
    all_false(bitset);
    printBitset(bitset);

    

    return 0;
}