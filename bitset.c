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