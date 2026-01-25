// Define all helper functions for hw2 in this file
#include "helpers2.h"

#include <stdlib.h>

int str_len(char* str) {
    if (str == NULL) {
        return 0;
    }

    int len = 0;

    while (*str != '\0') {
        ++len, ++str;
    }

    return len;
}

int str_cmp(const char *s1, const char *s2) {
    if (!s1 || !s2) {
        return 0;
    }

    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }

    return (unsigned char)*s1 - (unsigned char)*s2;
}

int str_cmp_n(char *str1, char *str2, size_t n) {
    if (n < 0 || !str1 || !str2) {
        return 0;
    }

    while (*str1 != '\0' && *str2 != '\0' && n > 0) {
        char s1 = *str1;
        char s2 = *str2;

        if (s1 != s2) {
            return (unsigned char)s1 - (unsigned char)s2;
        }

        ++str1, ++str2, --n;
    }


    return 0;
}

char* str_cpy(char *dest, const char *src) {
    if (!dest || !src) {
        return dest;
    }

    char *d = dest;
    while ((*d++ = *src++) != '\0');

    return dest;
}

char* str_cpy_n(char *dest, const char *src, size_t n) {
    if (n < 0 || !dest || !src) {
        return dest;
    }

    const char* p = NULL;
    char* d = dest;

    for (p = src; p - src < n && *p != '\0'; ++p) {
        *(d++) = *p;
    }

    for (; p - src < n; ++p) {
        *(d++) = '\0';
    }

    return dest;
}

char* clone_str(char* src, unsigned int len) {
    if (len < 0 || !src) {
        return NULL;
    }

    char* str = malloc(len + 1);

    for (int i = 0; i < len; ++i) {
        *(str + i) = *(src + i);
    }

    *(str + len) = '\0';

    return str;
}

char* find_str(char* haystack, char* needle) {
    if (!haystack || !needle) {
        return NULL;
    }

    if (*needle == '\0') { return haystack; }

    char* curr = haystack;

    while (*curr != *needle) {
        if (*curr == '\0') { return NULL; }
        ++curr;
    }

    while (*curr != '\0') {
        char* inner = curr;
        char* target = needle;
        bool matching = true;

        while (*target != '\0' && *inner != '\0') {
            if (*inner != *target) {
                matching = false;
                break;
            } else {
                ++inner, ++target;
            }
        }

        if (matching && *target == '\0') {
            return curr;
        }

        ++curr;
    }

    return NULL;
}

