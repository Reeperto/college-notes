#include "hw0.h"

#include "helpers0.h"

int main (int argc, char *argv[])
{
    int char_total = 0;
    for (int i = 0; i < argc; ++i) {
        int str_len = printArg(argv[i], i);
        char_total += (i == 0) ? 0 : str_len;
    }

    printf("Total characters: %d\n", char_total);

	return 0;
}
