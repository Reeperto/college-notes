#ifndef HELPERS_2_H
#define HELPERS_2_H

#include <stdlib.h>

typedef enum { false, true } bool;

int str_len(char* str);
char* str_cpy_n(char *dest, const char *src, size_t n);

char* clone_str(char* src, unsigned int len);
char* find_str(char* haystack, char* needle);

#endif
