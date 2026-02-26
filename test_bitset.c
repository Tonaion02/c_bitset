#include <stdio.h>
#include <stdlib.h>

#include "bitset.h"





int main()
{
    const unsigned int n = 10;
    CBitSet *p = create_bitset(n * WORD_SIZE);

    printf("capacity of bitset: %d\n", p->capacity);
    printf("size of bitset: %d\n", p->size);
    
    all_true(p);
    print_bitset(p);
    printf("\n");

    set_false(p, 2 * WORD_SIZE + 2);
    print_bitset(p);
    printf("\n");

    set_bit(p, 2 * WORD_SIZE + 2, 1);
    printf("After set bit\n");
    print_bitset(p);

    set_bit(p, 2 * WORD_SIZE + 2, 0);
    printf("After the second set bit\n");
    print_bitset(p);

    printf("print bitset\n");
    print_bitset(p);

    // const unsigned int n2 = 10;
    // // const unsigned int n_char_words_2 = 2 * 4 + n2 * sizeof(WORD_TYPE);
    // // char buffer2[n_char_words_2];
    // // Bitset *p_2 = (Bitset*)buffer2;
    // // p->capacity = n2;
    // // p->size = n2 * WORD_SIZE;

    // CBitSet *p_2 = create_bitset(n2 * WORD_SIZE);

    // all_true(p_2);
    // printf("and between p, p_2\n");
    // and(p, p_2);
    // print_bitset(p);

    // printf("or between p, p_2\n");
    // or(p, p_2);
    // print_bitset(p);
    
    // printf("not of p\n");
    // not(p);
    // print_bitset(p);

    // all_true(p);
    // printf("\n");
    // print_bitset(p);
    // set_bit(p, 3, 0);
    // printf("\n");
    // print_bitset(p);

    return 0;
}