# C_BITSET

C_Bitset is a simple implementation of a bitset in C.

## How the repository is organized
In this repository the principal file is bitset.h.
In bitset.h we have the definition of bitset and of the macros that are used to manipulate the bitset.
<br>
In bitset.c is implemented some methods that is used for debugging purposes.
The file predefined_bitset.h is an experiment that is used to make different type of bitset on the base of type of word that we want to use.
This is only an experiment and is not recommended to use it.
<br>
In test_bitset.c is contained a series of test that is used to understand what works and what not.
<br>
In the Makefile are contained some commands that are used to build and test bitset. But if you want only to use bitset, you can ignore this file.

## How to use c_bitset
To use c_bitset in you project, you can directly include in your file the .h file because this is built like a single .h library.
You can also define the type of word that you want to use in the bitset. It is important to underline that the kind of word that you decide to use, is the same for all the bitset that you will define.
``` C
#define WORD_TYPE unsigned int
#include "bitset.h" 
```
This is detail probably will be fixed with the xperiment of predefined_bitset.
The WORD_TYPE is set of default to char.

## Examples
Here we have an example that show the most of the operations that are possible to make in the current version of Bitset
``` C
#include <stdio.h>
#include "bitset.h"

int main(int argc, char **argv)
{
    Bitset *bitset;
    // This is the number of bits that we want to store
    int n = 10;

    // Create the bitset, this is the real initialization of bitset.
    create_bitset(bitset, n);

    // Access to the number of bits that we want to store
    printf("%d\n", bitset->size);

    // Access to the number of words that are used to store the bits
    // So we need a number_of_words that is number of bits divided by the
    // quantity of bit for each word. In this case the number of bits is 
    // n=10, the default type of word used is char, so we have 10 / 8 = 1.xxx
    // so the results is 2(we round always for excess).
    printf("%d\n", bitset->capacity);

    // Put all the bits of the bitset to true(1)
    all_true(bitset);

    // Put all the bits of the bitset to false(0)
    all_false(bitset);

    // Put the i-th bit to true(1)
    set_true(bitset, i);
    // Put the i-th bit to false(0)
    set_false(bitset, i);

    // Get the value of i-th bit and print it
    printf("%d\n", get_bit(bitset, i));

    // Free the memory occupied by the bitset
    // WARNING this make sense only because we are allocating on the heap
    free_bitset(bitset);

    return 0;
}
```