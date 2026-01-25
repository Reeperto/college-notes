// Eli Griffiths
// elimg

#include "hw2.h"
#include "helpers2.h"
#include "linkedlist.h"

int is_numeric(char c) {
    return ('0' <= c) && (c <= '9');
}

static int parse_date(char* str, int len, Date* date) {
    if (!str) {
        return false;
    }

    enum ParseState {
        MONTH,
        DAY,
        YEAR
    };

    int month = 0, day = 0, year = -1;
    enum ParseState state = MONTH;

    for (int i = 0; i < len; ++i) {
        char c = *(str + i);

        if (c == '/') {
            state += 1;
            continue;
        } else if (!is_numeric(c)) {
            return 0;
        }

        int char_dec = (c - '0');

        switch (state) {
        case MONTH:
            month = 10 * month + char_dec;
            break;
        case DAY:
            day = 10 * day + char_dec;
            break;
        case YEAR:
            year = (year == -1) ? 0 : year;
            year = 10 * year + char_dec;
            break;
        }
    }

    if (!(
        (state == YEAR)
        && (1 <= month && month <= 12)
        && (1 <= day   && day   <= 31)
        && (0 <= year  && year  <= 2025)
    )) {
        return false;
    }

    date->day = day;
    date->month = month;
    date->year = year;

    return true;
}

// Part 1 Functions to implement
int getDate(char* str, Date* myDate) {
    int len = str_len(str);
    bool success = parse_date(str, len, myDate);
    return success;
}

int cmpDate(const Date date1, const Date date2) {
    if (date1.year < date2.year) {
        return -1;
    } else if (date1.year > date2.year) {
        return 1;
    }

    if (date1.month < date2.month) {
        return -1;
    } else if (date1.month > date2.month) {
        return 1;
    }

    if (date1.day < date2.day) {
        return -1;
    } else if (date1.day > date2.day) {
        return 1;
    }

    return 0;
}

// Part 2 Functions to implement
int genreComparator(void* str1, void* str2) {
    if (!str1 || !str2) {
        return 0xBEEFCAFE;
    }

    char* p1 = str1, *p2 = str2;

    while (*p1 != '\0' && *p2 != '\0') {
        if (*p1 == *p2) {
            ++p1, ++p2;
        } else if (*p1 < *p2) {
            return -1;
        } else {
            return 1;
        }
    }

    if (*p1 == *p2) {
        return 0;
    } else if (*p1 < *p2) {
        return -1;
    } else {
        return 1;
    }
}

void genrePrinter(void* data, FILE* fp, int flag) {
    char* str = data;
    fprintf(fp, "%s", str);
}

void genreDeleter(void* data) {
    free(data);
}


/**
 * Returns a dynamically allocated instance of the generic linked list which contains all of the
 * genre categories in the alphabetical order. The function returns NULL on error (eg. NULL
 * pointer, empty string, empty genre)
 *
 * @param str A pointer to a list of genres separated by |
 * @return pointer to dynamically allocated list_t populated with a node per genre category.
 **/
list_t* getGenres(char* str) {
    list_t* list = NULL;

    if (!str) {
        goto on_error;
    }

    list = CreateList(genreComparator, genrePrinter, genreDeleter);

    char* genre_start = str;
    char* p_curr = str;

    while (*p_curr != '\0') {
        if (*p_curr == '|') {
            int genre_str_len = (p_curr - genre_start);

            if (genre_str_len > 0) {
                InsertInOrder(list, clone_str(genre_start, genre_str_len));
            } else {
                goto on_error;
            }

            genre_start = p_curr + 1;
        }

        ++p_curr;
    }

    // Handles the case where there is one genre, hence no '|'
    int genre_str_len = (p_curr - genre_start);

    if (genre_str_len > 0) {
        InsertInOrder(list, clone_str(genre_start, genre_str_len));
        goto on_success;
    } else {
        goto on_error;
    }


on_error:
    DestroyList(&list);
    return NULL;

on_success:
    return list;
}

// Part 2 Generic Linked List functions

/**
 * Search the list for a node with data equal to token. If found, return a pointer to the list
 * node. If token is not found or an error occurs (eg. NULL pointer, empty token, 0xBEEFCAFE error
 * case), return NULL.
 *
 * @param list The list to search in
 * @param token The data value to search for
 * @return pointer to node in the linked list for match
 **/
node_t* FindInList(list_t* list, void* token) {
    if (list == NULL) {
        return NULL;
    }

    node_t* result = NULL;
    node_t* node = list->head;

    while (node != NULL) {
        int cmp = list->comparator(node->data, token);

        if (cmp == 0xBEEFCAFE) {
            return NULL;
        } else if (cmp == 0) {
            return node;
        }

        node = node->next;
    }

    return NULL;
}

/**
 * Deletes a generic linked list by freeing all of the nodes using the Deleter function pointer
 * stored in the linked list. This function also frees the list_t pointer after freeing all of
 * the nodes.
 *
 * If the list is NULL, the function performs no operation.
 *
 * @param list A pointer to the dynamically allocated list node
 **/
void DestroyList(list_t** list_ptr)  {
    // TODO(eli): Double check this
    if (list_ptr == NULL || *list_ptr == NULL) {
        return;
    }

    list_t* list = *list_ptr;

    node_t* node = list->head;

    while (node != NULL) {
        node_t* next = node->next;       

        list->deleter(node->data);
        free(node);

        node = next;
    }

    free(*list_ptr);
    *list_ptr = NULL;
}

// Part 3 Functions to implement

/**
 * Prints a book_t struct to fp in TSV format in 2 formats based on flag.
 * If flag is 0 (debug print) all fields are printed in specified format:
 *   ISBN\tmm\tdd\tyyyy\tname\ttitle\tgenre(s)\n
 * If flag is set (non-zero), pretty print the book information in the following format:
 *   yyyy\tname\t"title"\tgenre(s)\n
 * In both cases, the genre categories are separated by a comma.
 *
 * If data is NULL, nothing is printed.
 *
 * @param data Pointer to book_t struct
 * @param fp Output file pointer to print output to (eg. STDOUT or open file)
 * @param flag Flag is non-zero for pretty print or 0 for debug print
 **/
void book_tPrinter(void* data, FILE*fp, int flag) {
    if (data == NULL) {
        return;
    }

    book_t* book = data;

    if (flag == 0) {
        fprintf(
            fp, "%d\t%02d\%02d\t%04d\t%s\t%s\t",
            book->ISBN,
            book->pubDate.month,
            book->pubDate.day,
            book->pubDate.year,
            book->name,
            book->title
        );
    } else {
        fprintf(
            fp, "%04d\t%s\t\"%s\"\t",
            book->pubDate.year,
            book->name,
            book->title
        );
    }

    PrintLinkedList(book->genres, fp, ",");
}

int book_tISBNAscComparator(void* lhs, void* rhs) {
    if (!lhs || !rhs) {
        return 0xBEEFCAFE;
    }

    book_t* book_lhs = lhs;
    book_t* book_rhs = rhs;

    unsigned int lhs_i = book_lhs->ISBN;
    unsigned int rhs_i = book_rhs->ISBN;

    if (lhs_i == rhs_i) {
        return 0;
    } else if (lhs_i < rhs_i) {
        return -1;
    } else {
        return 1;
    }
}

int book_tISBNDescComparator(void* lhs, void* rhs) {
    int cmp = book_tISBNAscComparator(lhs, rhs);
    return cmp == 0xBEEFCAFE ? cmp : -cmp;
}

void book_tDeleter(void* data) {
    book_t* book = data;

    DestroyList(&book->genres);
    free(book->name);
    free(book->title);

    free(book);
}

static bool parse_title(char* str, char** title_out, char** next_field_out) {
    bool quoted = (*str == '\"');

    char* title_start = str;
    char* title_end = NULL;
    char* next_field = NULL;

    if (quoted) {
        title_start += 1;
        title_end = find_str(title_start, "\",");
        next_field = title_end + 2;
    } else {
        title_end = find_str(title_start, ",");
        next_field = title_end + 1;
    }

    if (!title_end || *(title_end + 1) == '\0') { return false; }

    char* title = clone_str(title_start, title_end - title_start);
    if (!title) { return false; }

    *title_out = title;
    *next_field_out = title_end + 1;

    return true;
}

static bool parse_isbn(
    char* str,
    unsigned int* isbn_out,
    char** next_field_out
) {
    unsigned int isbn = 0;

    char* p = str;
    while (*p != ',') {
        char c = *p;
        if (c == '\0' || !is_numeric(c)) { 
            return false; 
        }

        isbn = isbn * 10 + (c - '0');
        ++p;
    }

    if (isbn == 0) {
        return false;
    }

    *isbn_out = isbn;

    if (*p == '\0') { 
        return false; 
    } else {
        *next_field_out = p + 1;
        return true;
    }
}

static bool parse_author(char* str, char** author_out, char** next_field_out) {
    char* first_name_start = str;
    char* first_name_end = find_str(str, ",");
    if (!first_name_end || *first_name_end == '\0') { return false; }

    char* last_name_start = first_name_end + 1;
    char* last_name_end = find_str(last_name_start, ",");
    if (!last_name_end || *last_name_end == '\0') { return false; }

    int first_name_len = first_name_end - first_name_start;
    int last_name_len = last_name_end - last_name_start;

    if (first_name_len < 0 || last_name_len < 0 || *last_name_end == '\0') { 
        return false; 
    }

    char* author = malloc(first_name_len + last_name_len + 2 + 1);
    str_cpy_n(author, last_name_start, last_name_len);
    str_cpy_n(author + last_name_len, ", ", 2);
    str_cpy_n(author + last_name_len + 2, first_name_start, first_name_len);

    *author_out = author;
    *next_field_out = last_name_end + 1;

    return true;
}

book_t* createBook(char* line) {
    if (!line) {
        return NULL;
    }

    book_t* book = calloc(1, sizeof(book_t));
    char* curr = line;

    bool title_parsed = parse_title(curr, &book->title, &curr);
    if (!title_parsed) { goto on_error; }

    bool isbn_parsed = parse_isbn(curr, &book->ISBN, &curr);
    if (!title_parsed) { goto on_error; }

    bool author_parsed = parse_author(curr, &book->name, &curr);
    if (!author_parsed) { goto on_error; }

    char* date_end = find_str(curr, ",");
    if (!date_end || *(date_end + 1) == '\0') { goto on_error; }
    bool date_parsed = parse_date(curr, date_end - curr, &book->pubDate);
    if (!date_parsed) { goto on_error; }
    curr = date_end + 1;

    list_t* genres = getGenres(curr);
    if (!genres) { goto on_error; }
    book->genres = genres;

    return book;

on_error:
    free(book->name);
    free(book->title);
    free(book);

    return NULL;
}

// static bool str_eq_n(char* str1, char* str2, unsigned int n) {
//     if (!str1 || !str2 || n < 0) {
//         return false;
//     }
//
//     while (*str1 != '\0' && *str2 != '\0' && n > 0) {
//         if (*str1 != *str2) {
//             return false;
//         } else {
//             ++str1, ++str2, --n;
//         }
//     }
//
//     if (n == 0) {
//         return true;
//     } else if (*str1 == '\0' && *str2 == '\0') {
//         return true;
//     } else {
//         return false;
//     }
// }

// Part 4 Functions to implement
int bookMatch(book_t* book, search_t* criterion) {
    if (!book || !criterion) {
        return -1;
    }

    bool matches = true;

    if (criterion->name != NULL) {
        // if (book->name == NULL) { return -1; }

        char* found = find_str(book->name, criterion->name);

        if (!found) {
            matches = false;
        }
    } else if (criterion->keyword != NULL) {
        // if (book->title == NULL || book->name) { return -1; }

        char* in_name = find_str(book->name, criterion->keyword);
        char* in_title = find_str(book->title, criterion->keyword);

        if (!in_name && !in_title) {
            matches = false;
        }
    } else if (criterion->ISBN != 0) {
        book_t temp = { .ISBN = criterion->ISBN };
        int cmp = book_tISBNAscComparator(&book->ISBN, &temp);
        if (cmp == 0xBEEFCAFE) { return -1; }

        if (cmp != 0) {
            matches = false;
        }
    } else if (
        criterion->pubDate.day != 0 
        && criterion->pubDate.month != 0 
        && criterion->pubDate.year
    ) {
        int cmp = cmpDate(criterion->pubDate, book->pubDate);

        if (cmp != 0) {
            matches = false;
        }
    } else if (criterion->genre != NULL) {
        node_t* res = FindInList(book->genres, criterion->genre);
        if (!res) {
            matches = false;
        }
    }

    return matches;
}

void PrintNLinkedList(list_t* list, FILE* fp, int NUM) {
    if (list == NULL || NUM < 0) { return; }

    node_t* node = list->head;

    if (NUM == 0) {
        while (node) {
            list->printer(node->data, fp, 0);
            node = node->next;
        }
    } else {
        while (node && NUM > 0) {
            list->printer(node->data, fp, 0);
            node = node->next;
            --NUM;
        }
    }
}
