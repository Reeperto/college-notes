#include "helpers1.h"

bool parse_mandatory_flag(enum Operation* op, char* dashflag)
{
    if (strlen(dashflag) != 2 || dashflag[0] != '-') { return false; }

    switch (dashflag[1]) {
        case 'h':
            return false;
            break;
        case 'U':
            *op = UPPERCASE;
            break;
        case 'L':
            *op = LOWERCASE;
            break;
        case 'T':
            *op = TITLECASE;
            break;
        case 't':
            *op = TERMFMT;
            break;
        case 'R':
            *op = REMOVAL;
            break;
        default:
            return false;
    }

    return true;
}

bool check_word_flag(char* dashflag)
{
    if (strlen(dashflag) != 2 
        || dashflag[0] != '-'
        || dashflag[1] != 'W') { return false; }

    return true;
}
