#ifndef S21_CAT_H_
#define S21_CAT_H_

#define APP_NAME "s21_cat"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct s21f {
    bool help;
    bool version;
    bool number;
    bool number_nonblank;
    bool show_ends;
    bool show_nonprinting;
    bool show_tabs;
    bool squeeze_blank;
} s21_cat_flags;

s21_cat_flags parse_flags(int argc, char* argv[], int* error);

#endif