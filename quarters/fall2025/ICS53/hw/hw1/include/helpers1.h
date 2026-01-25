// Define all helper functions for hw1 in this file

#include <stdbool.h>
#include <string.h>
#include <ctype.h>

enum Operation {
    LOWERCASE,
    UPPERCASE,
    TITLECASE,
    TERMFMT,
    REMOVAL,
};

bool parse_mandatory_flag(enum Operation* op, char* dashflag);
bool check_word_flag(char* dash_flag);
