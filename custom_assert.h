#ifndef _CUSTOM_ASSERT_H
#define _CUSTOM_ASSERT_H





#define GET_STRING_FROM_TOKEN(tokens) #tokens

#ifdef DEBUG
#include <stdio.h>

#ifdef WINDOWS
#define ASSERT(condition)			{																					\
										if (!(condition))																\
										{																				\
											printf("%s\n", GET_STRING_FROM_TOKEN(condition));							\
											printf("Erorr in file: %s in function: %s\n", __FILE__, __FUNCTION__);		\
										}																				\
									}
#endif

#ifdef LINUX
#define ASSERT(condition)			{																					\
										if(!(condition))																\
										{																				\
											printf("%s\n", GET_STRING_FROM_TOKEN(condition));							\
											printf("Erorr in file: %s in function: %s\n", __FILE__, __FUNCTION__);		\
											__builtin_trap();															\
										}																				\
									}
#endif

#endif

#ifndef ASSERT
	#define ASSERT(condition) ;
#endif

#endif