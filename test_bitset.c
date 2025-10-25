#include <stdio.h>
#include <stdlib.h>

#include "bitset.h"





int main()
{    
    // Bitset *bitset;

    // int n = 45;
    // create_bitset(bitset, n);
 
    // // T: print current capacity of Bitset
    // // T: NOTE please note that the capacity of Bitset reppresent the number of "WORDS"
    // // that are used to store the bits. The effective number of stored bits are size.
    // printf("capacity of bitset: %d\n", bitset->capacity);

    // printf("size of bitset: %d\n", bitset->size);
    
    // // T: put all the bits of bitset to true
    // all_true(bitset);
    // printf("word 2 of bitset: \n");
    // print_word_bitset(bitset->packed_data[2]);
    // printf("\n");
    // // printBitset(bitset);
    
    // // T: put all bits of bitset to false
    // all_false(bitset);
    // printf("word 2 of bitset: \n");
    // print_word_bitset(bitset->packed_data[2]);
    // printf("\n");
    // // printBitset(bitset);


    
    // T: TODO implement this idea for a stack allocated bitset.
    // T: NOTE you can use this trick even to allocate multiple bitset like a single piece of memory
    const unsigned int n = 10;
    const unsigned int n_char_words = 2 * 4 + n * sizeof(WORD_TYPE);
    char buffer[n_char_words];
    Bitset *p = (Bitset*)buffer; 
    p->capacity = n;
    p->size = n * WORD_SIZE;

    printf("capacity of bitset: %d\n", p->capacity);

    printf("size of bitset: %d\n", p->size);
    
    all_true(p);
    print_word_bitset(p->packed_data[2]);
    printf("\n");

    set_false(p, 2 * WORD_SIZE + 2);
    print_word_bitset(p->packed_data[2]);
    printf("\n");

    printf("print bitset\n");
    print_bitset(p);

    const unsigned int n2 = 10;
    const unsigned int n_char_words_2 = 2 * 4 + n2 * sizeof(WORD_TYPE);
    char buffer2[n_char_words_2];
    Bitset *p_2 = (Bitset*)buffer2;
    p->capacity = n2;
    p->size = n2 * WORD_SIZE;

    all_true(p_2);
    printf("and between p, p_2\n");
    and(p, p_2);
    print_bitset(p);

    printf("or between p, p_2\n");
    or(p, p_2);
    print_bitset(p);
    
    printf("not of p\n");
    not(p);
    print_bitset(p);

    return 0;
}