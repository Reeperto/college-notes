// Eli Griffiths
// elimg

#include "hw1.h"

int main(int argc, char* argv[])
{
    ArgParseResult res = parse_cmd_args(argc, argv);

    if (!res.valid_parse && !res.showed_usage) {
        return 1;
    } else if (!res.valid_parse && res.showed_usage) {
        return 0;
    }

    enum Operation operation = res.operation;
    char* remove_syms = res.remove_syms;

    Statistics stats = { .lines = 1 };
    WordMatcher wm = {0};
    ParserState state = {0};

    wm_init(&wm, res.stat_word);

    int num_read;
    while ((num_read = ps_read_stdin(&state)) > 0) {
        stats.characters += num_read;

        for (int i = 0; i < num_read; ++i) {
            char curr_char = state.read_buf[i];

            if (curr_char == '\n') {
                ++stats.lines;

                if (state.curr_line_len > stats.longest_line) {
                    stats.longest_line = state.curr_line_len;
                }

                state.curr_line_len = 0;
            } else {
                state.curr_line_len += 1;
            }

            if (!isspace(curr_char)) {
                state.start_of_word = !state.in_word;
                state.in_word = true;

                if (!state.seen_alpha && isalpha(curr_char)) {
                    state.start_of_alpha = true;
                    state.seen_alpha = true;
                } else {
                    state.start_of_alpha = false;
                }

                wm_add_char(&wm, curr_char);
            } else {
                if (state.in_word) {
                    stats.words += 1;
                    stats.word_occurences += wm_check(&wm) ? 1 : 0;
                    wm_reset(&wm);
                }

                state.in_word = false;
                state.seen_alpha = false;
            }

            switch (operation) {
                case OP_UPPERCASE: {
                    ps_wb_add_char(&state, toupper(state.read_buf[i]));
                    break;
                }
                case OP_LOWERCASE: {
                    ps_wb_add_char(&state, tolower(state.read_buf[i]));
                    break;
                }
                case OP_TITLECASE: {
                    if (state.start_of_alpha) {
                        ps_wb_add_char(&state, toupper(state.read_buf[i]));
                    } else {
                        ps_wb_add_char(&state, tolower(state.read_buf[i]));
                    }

                    break;
                }
                case OP_REMOVAL: {
                    bool should_remove = false;

                    for (int i = 0; i < strlen(remove_syms); ++i) {
                        if (curr_char == remove_syms[i]) {
                            should_remove = true;
                            break;
                        }
                    }

                    if (!should_remove) {
                        ps_wb_add_char(&state, state.read_buf[i]);
                    }

                    break;
                }
                case OP_TERMFMT: {
                    if (curr_char == '\n') {
                        ps_tb_flush(&state);
                        fputc('\n', stdout);
                    } else {
                        if (state.tb_len == TERM_WIDTH) {
                           ps_tb_flush(&state);
                           fputc('\n', stdout);
                        }

                        ps_tb_add_char(&state, curr_char);
                    }

                    break;
                }
                default: {
                    assert(false);
                    break;
                }
            }

        }

        ps_wb_flush(&state);
        state.total_read += num_read;
    }

    if (state.total_read == 0) {
        print_usage(true);
        return 1;
    }

    if (state.curr_line_len > stats.longest_line) {
        stats.longest_line = state.curr_line_len;
    }

    if (state.tb_len != 0) {
        ps_tb_flush(&state);
    }

    if (state.in_word) {
        stats.words += 1;
        stats.word_occurences += wm_check(&wm) ? 1 : 0;
        wm_reset(&wm);
    }

    fprintf(stderr, "%d\n", stats.characters);
    fprintf(stderr, "%d\n", stats.lines);
    fprintf(stderr, "%d\n", stats.words);
    fprintf(stderr, "%d\n", stats.longest_line);

    if (wm.word != NULL) {
        fprintf(stderr, "%d\n", stats.word_occurences);
    }

    return 0;
}
