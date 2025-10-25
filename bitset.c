#include <stdio.h>

#include "bitset.h"





void print_word_bitset(WORD_TYPE word)
{
    int i;
    for(i = (sizeof(WORD_TYPE) * 8) -1; i >= 0; i--)
    {
        // T: TODO check if it is useful to use _internal_index in this case
        int b = word & (1 << i);
        printf("%d", (int)(b != 0));
    }
}

// T: TODO check if this method works
void print_bitset(Bitset *bitset_p)
{
    printf("size in word bitset: %d\n", bitset_p->capacity);
    for(int i = 0; i < bitset_p->capacity; i++)
    {
        for(int j = WORD_SIZE -1; j >= 0; j--)
        {  
            // T: TODO print only bit that have an index that is smaller than the size of the bitset
            if(i * WORD_SIZE + j < bitset_p->size)
            {
                int b = bitset_p->packed_data[i] & (1 << _internal_index(j));
                printf("%d", (int)(b != 0));    
            }
        }
        printf("\n");
    }
}