#include "helpers0.h"

#include <string.h>

//Function to print out a single arugment to the screen
int printArg(char* arg_str, int pos)
{
    printf("argv[%d]: %s\n", pos, arg_str);
    return strlen(arg_str);
}
