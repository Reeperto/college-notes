// Define all helper functions for hw1 in this file

#include <stdbool.h>

typedef struct {
    int characters;
    int lines;
    int words;

    int longest_line;

    int word_occurences;
} Statistics;

enum Operation {
    OP_NONE,
    OP_LOWERCASE,
    OP_UPPERCASE,
    OP_TITLECASE,
    OP_TERMFMT,
    OP_REMOVAL,
};

enum Operation letter_to_op(char flag);

enum ArgParseState {
    STATE_FLAG,
    STATE_WORD_ARG,
    STATE_REMOVAL_ARG,
};

typedef struct {
    bool valid_parse;
    bool showed_usage;

    char* stat_word;
    char* remove_syms;

    enum Operation operation;
} ArgParseResult;

void print_usage(bool is_error);
ArgParseResult parse_cmd_args(int argc, char* argv[]);

#define BUFFER_SIZE 256
#define TERM_WIDTH 80

typedef struct {
    char read_buf[BUFFER_SIZE];

    char work_buf[BUFFER_SIZE];
    int wb_len;

    char term_buf[TERM_WIDTH];
    int tb_len;

    int total_read;
    int curr_line_len;

    bool in_word;

    bool seen_alpha;
    bool start_of_alpha;

    bool start_of_word;
} ParserState;

int ps_read_stdin(ParserState* ps);

void ps_wb_add_char(ParserState* ps, char c);
void ps_wb_flush(ParserState* ps);

void ps_tb_add_char(ParserState* ps, char c);
void ps_tb_flush(ParserState* ps);

typedef struct {
    char* word;
    int word_len;

    int checked_len;
    bool is_matching;
} WordMatcher;

void wm_init(WordMatcher* wm, char* word);
bool wm_check(WordMatcher* wm);
void wm_reset(WordMatcher* wm);
void wm_add_char(WordMatcher* wm, char c);
