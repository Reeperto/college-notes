#include "helpers2.h"
#include "acutest.h"
#include "hw2.h"

#define ARR_LEN(arr) (sizeof((arr)) / sizeof((arr)[0]))

void test_date_parsing() {
    char hard_neg_str[] = "17/01/2000";
    Date date;

    int success = getDate(hard_neg_str, &date);
    TEST_CHECK(success == 0);

    char* positive_str = "05/21/1980";
    success = getDate(positive_str, &date);
    TEST_CHECK(success == 1);

    char* null_str = NULL;
    success = getDate(null_str, &date);
    TEST_CHECK(success == 0);

    char* invalid_str = "hello world! 05/21/1980";
    success = getDate(invalid_str, &date);
    TEST_CHECK(success == 0);
}

void test_date_cmp() {
    Date date1 = { 5, 21, 1980 };
    Date date2 = { 1, 1, 2022 };

    int cmp = cmpDate(date1, date2);
    TEST_CHECK(cmp == -1);
}

void test_genre_cmp() {
    char* null = NULL;
    char* str1 = "Mystery";
    char str2[] = "Classic";
    char str3[12] = "Self Help";
    char str4[4] = "Self";

    char* str5 = calloc(5,1);
    strncpy(str5,str4,4);

    TEST_CHECK(genreComparator(str1, str2) == 1);
    TEST_CHECK(genreComparator(str2, str1) == -1);
    TEST_CHECK(genreComparator(str2, str2) == 0);
    TEST_CHECK(genreComparator(str3, str5) == 1);
    TEST_CHECK(genreComparator(null, str1) == 0xBEEFCAFE);
    TEST_CHECK(genreComparator(null, null) == 0xBEEFCAFE);
    TEST_CHECK(genreComparator(str1, null) == 0xBEEFCAFE);

    free(str5);
}

void test_get_genre() {
    list_t* valid_genres[] = {
        getGenres("Fiction"),
        getGenres("Fiction|Mystery|Classic"),
        getGenres("Juvenile|Fiction|Young Adult|Family|Mystery|Classic"),
    };

    int valid_genres_len[] = {
        1,
        3,
        6,
    };

    list_t* invalid_genres[] = {
        getGenres("Juvenile||Classic"),
        getGenres("|Classic"),
        getGenres("Classic|"),
    };

    for (int i = 0; i < ARR_LEN(valid_genres); ++i) {
        TEST_CASE_("Valid Genre %d", i + 1);
        TEST_CHECK(valid_genres[i] != NULL);
        TEST_CHECK(valid_genres[i]->length == valid_genres_len[i]);
        DestroyList(&valid_genres[i]);
        TEST_CHECK(valid_genres[i] == NULL);
    }

    for (int i = 0; i < ARR_LEN(invalid_genres); ++i) {
        TEST_CASE_("Invalid Genre %d", i + 1);
        TEST_CHECK(invalid_genres[i] == NULL);
    }
}

void test_genre_find() {
    list_t* single = getGenres("Fiction");
    list_t* full = getGenres("Juvenile|Fiction|Young Adult|Family|Mystery|Classic");

    TEST_CHECK(FindInList(single, NULL) == NULL);

    TEST_CHECK(FindInList(single, "Fiction") == single->head);
    TEST_CHECK(FindInList(single, "Juvenile") == NULL);

    TEST_CHECK(FindInList(full, "Juvenile") != NULL);
    TEST_CHECK(FindInList(full, "Mystery") != NULL);
    TEST_CHECK(FindInList(full, "Young Adults") == NULL);
    
    DestroyList(&single);
    DestroyList(&full);
}

void test_find_str() {
    typedef struct {
        const char *name;
        char *haystack;
        char *needle;
        int expected_offset; // -1 for NULL expected
    } FindStrTest;

    FindStrTest tests[] = {
        // Basic functionality
        { "match_middle", "hello world", "world", 6 },
        { "match_start", "abcdef", "abc", 0 },
        { "match_end", "abcdef", "def", 3 },
        { "no_match", "abcdef", "gh", -1 },

        // Empty string cases
        { "empty_needle", "abc", "", 0 },
        { "both_empty", "", "", 0 },
        { "empty_haystack", "", "a", -1 },

        // Repeated / overlapping patterns
        { "overlap", "aaaaa", "aa", 0 },
        { "repeated_pattern", "abababab", "abab", 0 },
        { "middle_match", "abcabcabc", "cab", 2 },

        // Case sensitivity
        { "case_mismatch", "Hello World", "world", -1 },
        { "case_match", "Hello World", "World", 6 },

        // Special characters
        { "comma_search", "a,b,c", ",", 1 },
        { "tab_search", "one\ttwo\tthree", "\t", 3 },
        { "newline_search", "line1\nline2", "\n", 5 },

        // Long or non-matching
        { "needle_longer", "short", "longneedle", -1 },
        { "almost_match", "aaaa", "aaaaa", -1 }
    };

    for (int i = 0; i < ARR_LEN(tests); ++i) {
        FindStrTest t_case = tests[i];

        TEST_CASE(t_case.name);
        char* res = find_str(t_case.haystack, t_case.needle);

        if (t_case.expected_offset == -1) {
            TEST_CHECK(res == NULL);
        } else {
            TEST_CHECK(res != NULL);
            TEST_CHECK(res == t_case.haystack + t_case.expected_offset);
        }
    }
}

void test_book_create() {
    book_t* book1 = createBook("Linear Algebra,185326895,Friedberg,Guy,05/28/2004,Non Fiction|Math\n");
    TEST_CHECK(book1 != NULL);
    book_tDeleter(book1);

    book_t* book2 = createBook("The Name of the Wind,4040799780,Patrick,Rothfuss,03/27/2007,Fiction|Fantasy|Heroic\n");
    TEST_CHECK(book2 != NULL);
    book_tDeleter(book2);

    book_t* book3 = createBook(NULL);
    TEST_CHECK(book3 == NULL);

    book_t* book4 = createBook("The Complete Works of William Shakespeare,185326895,William,Shakespeare,12/35/3333,Drama|Fiction|Classic\n");
    TEST_CHECK(book4 == NULL);
}

void test_book_match() {
    search_t search = {0};
}

TEST_LIST = {
    { "Date Parsing", test_date_parsing },
    { "Date Cmp", test_date_cmp },
    { "Genre Cmp", test_genre_cmp },
    { "Genre Get", test_get_genre },
    { "Genre Find", test_genre_find },
    { "Str Find", test_find_str },
    { "Book Create", test_book_create },
    { NULL, NULL}
};
