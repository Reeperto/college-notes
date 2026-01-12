#include "helpers1.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define USAGE_MSG "Usage: ./formattxt -L | -U | -T | -t | -R SYMBOLS [-W WORD]\n\n"

void print_usage(bool is_error) {
    if (is_error) {
        fprintf(stderr, "ERROR! " USAGE_MSG);
    } else {
        fprintf(stdout, USAGE_MSG);
    }
}

enum Operation letter_to_op(char flag)
{
    switch (flag) {
        case 'U':
            return OP_UPPERCASE;
        case 'L':
            return OP_LOWERCASE;
        case 'T':
            return OP_TITLECASE;
        case 't':
            return OP_TERMFMT;
        case 'R':
            return OP_REMOVAL;
    }

    return OP_NONE;
}

ArgParseResult parse_cmd_args(int argc, char* argv[]) {
    enum ArgParseState state = STATE_FLAG;
    enum Operation operation = OP_NONE;

    char* word_arg = NULL;
    char* remove_arg = NULL;

    for (int i = 1; i < argc; ++i) {
        char* arg = argv[i];

        switch (state) {
            case STATE_FLAG: {
                // Flags must be a dash followed by a single character
                if (arg[0] != '-' && strlen(arg) != 2) { goto usage_error; }

                // Help and word count are not operations, and thus handled separately
                if (arg[1] == 'h') { 
                    goto usage_help; 
                } else if (arg[1] == 'W') { 
                    state = STATE_WORD_ARG;
                    break;
                }

                // At this point, flags should only map to operations, 
                // of which only one can occur at time.
                if (operation != OP_NONE) {
                    goto usage_error;
                }

                operation = letter_to_op(arg[1]);

                if (operation == OP_NONE) {
                    // At this point, all possible flags have been checked 
                    // for, and so OP_NONE means the flag is invalid.
                    goto usage_error;
                } else if (operation == OP_REMOVAL) {
                    state = STATE_REMOVAL_ARG;
                    break;
                }

                break;
            }

            case STATE_WORD_ARG: {
                word_arg = arg;
                state = STATE_FLAG;
                break;
            }

            case STATE_REMOVAL_ARG: {
                remove_arg = arg;
                state = STATE_FLAG;
                break;
            }
        }
    }

    if (state != STATE_FLAG || operation == OP_NONE) {
        // The parser should always be in a state looking for a new flag, 
        // otherwise some arguments will be missing. Additionally, a valid parse
        // must have a valid operation.
        goto usage_error;
    }

    return (ArgParseResult){
        .valid_parse = true,
        .operation = operation,
        .remove_syms = remove_arg,
        .stat_word = word_arg,
    };

usage_error:
    print_usage(true);
    return (ArgParseResult){ .valid_parse = false };

usage_help:
    print_usage(false);
    return (ArgParseResult){ .valid_parse = false, .showed_usage = true };
}

int ps_read_stdin(ParserState* ps) {
    return fread(ps->read_buf, 1, BUFFER_SIZE, stdin);
}

void ps_wb_add_char(ParserState* ps, char c) {
    assert(ps->wb_len < BUFFER_SIZE);
    ps->work_buf[ps->wb_len++] = c;
}

void ps_wb_flush(ParserState* ps) {
    fwrite(ps->work_buf, 1, ps->wb_len, stdout);
    ps->wb_len = 0;
}

void ps_tb_add_char(ParserState* ps, char c) {
    assert(ps->tb_len <= TERM_WIDTH);
    ps->term_buf[ps->tb_len++] = c;
}

void ps_tb_flush(ParserState* ps) {
    fwrite(ps->term_buf, 1, ps->tb_len, stdout);
    ps->tb_len = 0;
}

void wm_init(WordMatcher* wm, char* word) {
    *wm = (WordMatcher){
        .word = word,
        .word_len = word != NULL ? strlen(word) : 0,
        .is_matching = true,
        .checked_len = 0
    };
}

bool wm_check(WordMatcher* wm) {
    return (wm->is_matching) 
        && (wm->checked_len == wm->word_len);
}

void wm_reset(WordMatcher* wm) {
    wm->checked_len = 0;
    wm->is_matching = true;
}

void wm_add_char(WordMatcher* wm, char c) {
    if (wm->checked_len < wm->word_len) {
        if (wm->word[wm->checked_len] != c) {
            wm->is_matching = false;
        }
    }

    wm->checked_len += 1;
}
