NAME_OF_TEST_BITSET = test_bitset.exe
PATH_TO_DIRECTORY = C:/source/C/c_bitset

test_bitset:
	gcc bitset.h bitset.c test_bitset.c -o $(NAME_OF_TEST_BITSET)
	./$(NAME_OF_TEST_BITSET)

test_bitset_debug:
	gcc -g bitset.h bitset.c test_bitset.c -o $(NAME_OF_TEST_BITSET)
	gdb --directory $(PATH_TO_DIRECTORY) ./$(NAME_OF_TEST_BITSET)

clean:
	rm -f *.o *.exe