// Eli Griffiths
// elimg

#include "hw1.h"

#define BUFFER_SIZE 256

void print_usage() { fprintf(stderr, USAGE_MSG); }

typedef struct {
    int characters;
    int lines;
    int words;

    int longest_line;

    int word_occurences
} Statistics;

int main(int argc, char* argv[])
{
    bool parse_valid;

    enum Operation operation = 0;
    char* stat_word = NULL;
    char* remove_syms = NULL;

    switch (argc) {
        case 2: { // Single flags, _no removal_
            parse_valid = parse_mandatory_flag(&operation, argv[1]);
            if (operation == REMOVAL) { parse_valid = false; }
            break;
        }
        case 3: { // [-R SYMBOLS]
            parse_valid = parse_mandatory_flag(&operation, argv[1]);
            remove_syms = argv[2];
            break;
        }
        case 4: { // [-W WORD]
            parse_valid = parse_mandatory_flag(&operation, argv[1]);
            if (!parse_valid) { break; }
            parse_valid = check_word_flag(argv[2]);
            break;
        }
    }

    if (!parse_valid) {
        print_usage();
        return EXIT_FAILURE;
    }

    Statistics stats = {
        .lines = 1
    };

    char read_buf[BUFFER_SIZE];
    char work_buf[BUFFER_SIZE];

    int total_read = 0;
    int n_read;

    bool in_whitespace = false;

    while ((n_read = fread(read_buf, 1, BUFFER_SIZE, stdin)) > 0) {
        stats.characters += n_read;

        int work_buf_size = 0;
        for (int i = 0; i < n_read; ++i) {
            char curr_char = read_buf[i];

            if (curr_char == '\n') {
               ++stats.lines;
            }

            work_buf[i] = toupper(read_buf[i]);
            ++work_buf_size;
        }

        fwrite(work_buf, 1, work_buf_size);
    }

    if (total_read == 0) {
        print_usage();
        return EXIT_FAILURE;
    }

    fprintf(stderr, "%d\n", stats.characters);
    fprintf(stderr, "%d\n", stats.lines);
    fprintf(stderr, "%d\n", stats.words);
    fprintf(stderr, "%d\n", stats.longest_line);

    if (stat_word != NULL) {
        fprintf(stderr, "%d\n", stats.word_occurences);
    }

    return 0;
}
