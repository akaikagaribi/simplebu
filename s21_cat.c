#include "s21_cat.h"

void print_args(s21_cat_args args);

int main(int argc, char* argv[]) {
    int error = 0;
    s21_cat_args args = parse_args(argc, argv, &error);
    if (error == 0) {
        if (args.help) {
            (void)print_help();
        } else if (args.version) {
            (void)print_version();
        } else {
            (void)parse_files(argc, argv, &error);
        }
    }
    return error;
}

void cat(char* filename, int* error) {
    FILE* file;
    if (strcmp(filename, "-") == 0) {
        file = stdin;
        // fscanf(file, )
    } else {
        file = fopen(filename, "r");
    }
    if (file == NULL) {
        printf("%s: %s: No such file or directory\n", APP_NAME, filename);
        *error += 1;
    }
    if (*error == 0) {
        int ch = getc(file);
        while (ch >= 0) {
            // Тут будет дальнейшая логика
            (void)putc(ch, stdout);
            ch = getc(file);
        }
    }
    if (*error == 0) {
        (void)fclose(file);
    }
}

void print_help() {
    (void)printf("Usage: %s [PARAMS]... [FILE]...\n", APP_NAME);
}

void print_version() {
    (void)printf("%s (42 simplebashutils) %s\n", APP_NAME, APP_VERSION);
}

void parse_files(int argc, char* argv[], int* error) {
    for (int i = 1; i < argc && *error == 0; i++) {
        char* cur_arg = argv[i];
        if ((cur_arg[0] == '-' && cur_arg[1] == '\0') || cur_arg[0] != '-') {
            (void)cat(cur_arg, error);
        }
    }
    if (argc == 1) {
        (void)cat("-", error);
    }
}

s21_cat_args parse_args(int argc, char* argv[], int* error) {
    s21_cat_args args = {};
    bool ensure_number_disabled = false;
    for (int i = 1; i < argc && *error == 0; i++) {
        char* cur_arg = argv[i];
        if (cur_arg[0] == '-' && cur_arg[1] != '-') {
            for (int j = 1; cur_arg[j] != '\0' && *error == 0; j++) {
                switch (cur_arg[j]) {
                    case 'A':
                        args.show_nonprinting = true;
                        args.show_ends = true;
                        args.show_tabs = true;
                        break;
                    case 'b':
                        args.number_nonblank = true;
                        break;
                    case 'e':
                        ensure_number_disabled = true;
                        args.show_nonprinting = true;
                        args.show_ends = true;
                        break;
                    case 'E':
                        args.show_ends = true;
                        break;
                    case 'n':
                        args.number = true;
                        break;
                    case 's':
                        args.squeeze_blank = true;
                        break;
                    case 't':
                        args.show_nonprinting = true;
                        args.show_tabs = true;
                        break;
                    case 'T':
                        args.show_tabs = true;
                        break;
                    case 'u':
                        break;
                    case 'v':
                        args.show_nonprinting = true;
                        break;
                    default:
                        *error += 1;
                        (void)printf("%s: invalid option -- '%c'\n", APP_NAME,
                                     cur_arg[j]);
                        (void)printf("Try '%s --help' for more information.\n",
                                     APP_NAME);
                        break;
                }
            }
        } else if (cur_arg[0] == '-' && cur_arg[1] == '-') {
            if (strcmp(cur_arg, "--show-all") == 0) {
                args.show_nonprinting = true;
                args.show_ends = true;
                args.show_tabs = true;
            } else if (strcmp(cur_arg, "--number-nonblank") == 0) {
                args.number_nonblank = true;
            } else if (strcmp(cur_arg, "--show-ends") == 0) {
                args.show_ends = true;
            } else if (strcmp(cur_arg, "--number") == 0) {
                args.number = true;
            } else if (strcmp(cur_arg, "--squeeze-blank ") == 0) {
                args.squeeze_blank = true;
            } else if (strcmp(cur_arg, "--show-tabs") == 0) {
                args.show_tabs = true;
            } else if (strcmp(cur_arg, "--show-nonprinting") == 0) {
                args.show_nonprinting = true;
            } else if (strcmp(cur_arg, "--help") == 0) {
                i = __INT_MAX__ - 1;
                args.help = true;
                args.number = false;
                args.number_nonblank = false;
                args.show_ends = false;
                args.show_nonprinting = false;
                args.show_tabs = false;
                args.squeeze_blank = false;
                args.version = false;
            } else if (strcmp(cur_arg, "--version") == 0) {
                i = __INT_MAX__ - 1;
                args.help = false;
                args.number = false;
                args.number_nonblank = false;
                args.show_ends = false;
                args.show_nonprinting = false;
                args.show_tabs = false;
                args.squeeze_blank = false;
                args.version = true;
            } else {
                *error += 1;
                (void)printf("%s: invalid option -- '%s'\n", APP_NAME, cur_arg);
                (void)printf("Try '%s --help' for more information.\n",
                             APP_NAME);
            }
        }
    }
    if (ensure_number_disabled) {
        args.number = false;
    }
    return args;
}

// ОЧЕНЬ СТРАШНЫЙ КОД
void print_args(s21_cat_args args) {
    (void)printf("{\n");
    (void)printf("    \"help\": %s,\n", args.help ? "true" : "false");
    (void)printf("    \"version\": %s,\n", args.version ? "true" : "false");
    (void)printf("    \"number\": %s,\n", args.number ? "true" : "false");
    (void)printf("    \"number_nonblank\": %s,\n",
                 args.number_nonblank ? "true" : "false");
    (void)printf("    \"show_ends\": %s,\n", args.show_ends ? "true" : "false");
    (void)printf("    \"show_nonprinting\": %s,\n",
                 args.show_nonprinting ? "true" : "false");
    (void)printf("    \"show_tabs\": %s,\n", args.show_tabs ? "true" : "false");
    (void)printf("    \"squeeze_blank\": %s\n",
                 args.squeeze_blank ? "true" : "false");
    (void)printf("}\n");
}