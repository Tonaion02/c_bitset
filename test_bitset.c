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

    CBitSet *p2 = clone_bitset(p);
    printf("capacity of p2: %d\n", p2->capacity);
    printf("size of p2: %d\n", p2->size);
    print_bitset(p2);
    printf("\n");

    // p = resize_bitset(p, (n * WORD_SIZE) - 12);
    p = resize_bitset(p, 7);
    printf("Resize bitset\n");
    print_bitset(p);

    return 0;
}