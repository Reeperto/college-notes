#include "constants2.h"
#include "helpers2.h"
#include "hw2.h"

int main(int argc, char* argv[]) {
    search_t criterion = {0};

    // Required option
    int I_flag = 0;
    int D_flag = 0;
    int G_flag = 0;
    int N_flag = 0;
    int K_flag = 0;

    // Optional flags
    int NUM_arg = 0;
    char ORDER_arg = 'n';   // default no order
    char* OUTFILE = NULL;

    // Use basic getopt to parse flags and respective arguments
    int c;
    while ((c = getopt(argc, argv, "I:D:G:N:K:Hn:ado:")) >= 0) {
        switch (c) {
            case 'I':
                I_flag += 1;
                criterion.ISBN = atoi(optarg);
                break;
            case 'D':
                D_flag += 1;
                if(!getDate(optarg,&criterion.pubDate))
                    return EXIT_FAILURE;
                break;
            case 'G':
                G_flag += 1;
                criterion.genre = optarg;
                break;
            case 'N':
                N_flag += 1;
                criterion.name = optarg;
                break;
            case 'K':
                K_flag += 1;
                criterion.keyword = optarg;
                break;
            case 'H':
                fprintf(stdout, USAGE_MSG);
                return EXIT_SUCCESS;
            case 'n':
                NUM_arg = atoi(optarg);
                break;
            case 'o':
                OUTFILE = optarg;
                break;
            case 'a':
            case 'd':
                ORDER_arg = c;
                break;
            default:
                fprintf(stderr, USAGE_MSG);
                return EXIT_FAILURE;
        }
    }

    // validate a Search mode was specified - Does not check for more than 1
    int active_flag_count = I_flag + D_flag + G_flag + N_flag + K_flag;
    if (active_flag_count == 0)
    {
        fprintf(stderr, "ERROR: Search mode was not specified.\n\n" USAGE_MSG);
        return EXIT_FAILURE;
    }

    // INSERT YOUR IMPLEMENTATION HERE

    // TODO(eli): Multiple arguments
    // if (active_flag_count > 1) {
    //     fprintf(stderr, USAGE_MSG);
    //     return 1;
    // }

    if (
        I_flag > 1
        || D_flag > 1
        || G_flag > 1
        || N_flag > 1
        || K_flag > 1
    ) {
        fprintf(stderr, USAGE_MSG);
        return 1;
    }

    list_t* match_list = NULL;
    int (*list_cmp)(void*, void*) = NULL;
    void (*list_insert)(list_t* list, void* val_ref) = NULL;

    switch (ORDER_arg) {
        case 'n':
            list_cmp = (void*)book_tISBNAscComparator;
            list_insert = InsertAtTail;
            break;
        case 'a':
            list_cmp = (void*)book_tISBNAscComparator;
            list_insert = InsertInOrder;
            break;
        case 'd':
            list_cmp = (void*)book_tISBNDescComparator;
            list_insert = InsertInOrder;
            break;
        default:
            return 1;
    }

    FILE* output_file = NULL;

    if (OUTFILE) {
        FILE* fp_param = fopen(OUTFILE, "w");
        if (!fp_param) { return 3; }
        output_file = fp_param;
    } else {
        output_file = stdout;
    }

    match_list = CreateList(list_cmp, book_tPrinter, book_tDeleter);

    if (!match_list) {
        return 4;
    }

    char* line = NULL;
    size_t line_cap = 0;
    ssize_t line_size = 0;
    size_t total_read = 0;

    while ((line_size = getline(&line, &line_cap, stdin)) > 0) {
        book_t* book = createBook(line);

        if (!book) {
            free(line);
            DestroyList(&match_list);
            return 2;
        }

        int res = bookMatch(book, &criterion);

        if (res == -1) {
            return 2;
        } else if (res == 1) {
            list_insert(match_list, book);
        } else {
            book_tDeleter(book);
        }

        total_read += line_size;
    }

    free(line);

    if (total_read == 0) {
        return 2;
    }

    PrintNLinkedList(match_list, output_file, NUM_arg);
    DestroyList(&match_list);

    return 0;
}
