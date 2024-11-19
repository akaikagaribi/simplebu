#ifndef S21_CAT_H_
#define S21_CAT_H_

#define APP_NAME "s21_cat"
#define APP_VERSION "0.1 pre alpha test"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct s21ca {
    bool help;
    bool version;
    bool number;
    bool number_nonblank;
    bool show_ends;
    bool show_nonprinting;
    bool show_tabs;
    bool squeeze_blank;
} s21_cat_args;

void cat(char* filename, s21_cat_args args, int* ppch, int* pch, int* ch,
         int* lineno, int* error);
void print_help();
void print_version();
void parse_files(int argc, char* argv[], s21_cat_args args, int* error);
s21_cat_args parse_args(int argc, char* argv[], int* error);

#endif