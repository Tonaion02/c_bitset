#include <stdio.h>

#include "bitset.h"





void printBitsetFromWord(WORD_TYPE word)
{
    int i;
    for(i = (sizeof(WORD_TYPE) * 8) -1; i >= 0; i--)
    {
        int b = word & (1 << _internal_index(i));
        printf("%d", (int)(b != 0));
    }
}

void printBitset(Bitset bitset)
{
    printf("size in word bitset: %d\n", bitset.capacity);
    for(int i = 0; i < bitset.capacity; i++)
    {
        for(int j = WORD_SIZE -1; j >= 0; j--)
        {  
            // T: FIX print only bit that have an index that is smaller than the size of the bitset
            if(i * WORD_SIZE + j < bitset.size)
            {
                int b = bitset.packed_data[i] & (1 << _internal_index(j));
                printf("%d", (int)(b != 0));    
            }
        }
        printf("\n");
    }
}