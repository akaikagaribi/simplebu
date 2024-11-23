#ifndef S21_GREP_H_
#define S21_GREP_H_

#define APP_NAME "s21_grep"
#define APP_VERSION "0.1 pre alpha test"
#define LINE_SIZE 4096

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s21ga {
    bool help;
    bool version;
    bool case_insensetive;
    bool invert;
    bool only_count;
    bool only_filenames;
    bool number;
    bool no_filenames;
    bool supress_errors;
    bool only_matches;
    char filenames[LINE_SIZE];
    char regex[LINE_SIZE];
} s21_grep_args;

void print_help();
void print_version();
int add_str_to_str(char* first, char* second, bool is_file);
int asts_from_file(char* string, char* filename);
void parse_args(int argc, char* argv[], s21_grep_args* args, int* error);

#endif