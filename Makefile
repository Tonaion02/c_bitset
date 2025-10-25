NAME_OF_TEST_BITSET = test_bitset.exe
PATH_TO_DIRECTORY = C:/source/C/c_bitset

test_bitset:
	gcc custom_assert.h bitset.h bitset.c test_bitset.c -o $(NAME_OF_TEST_BITSET)
	./$(NAME_OF_TEST_BITSET)

test_bitset_debug:
	gcc -DDEBUG -DWINDOWS -g custom_assert.h bitset.h bitset.c test_bitset.c -o $(NAME_OF_TEST_BITSET)
	gdb --directory $(PATH_TO_DIRECTORY) ./$(NAME_OF_TEST_BITSET)

clean:
	rm -f *.o *.exe