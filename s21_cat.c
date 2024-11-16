#include "s21_cat.h"

void print_flags(s21_cat_flags flags);

int main(int argc, char* argv[]) {
    int error = 0;
    s21_cat_flags flags = parse_flags(argc, argv, &error);
    if (error == 0) {
        (void)print_flags(flags);
    }
    return error;
}

s21_cat_flags parse_flags(int argc, char* argv[], int *error) {
    s21_cat_flags flags;
    for (int i = 1; i < argc && *error == 0; i++) {
        char *cur_arg = argv[i];
        if (cur_arg[0] == '-' && cur_arg[1] != '-') {
            for (int j = 1; cur_arg[j] != '\0' && *error == 0; j++) {
                switch (cur_arg[j]) {
                case 'A':
                    flags.show_nonprinting = true;
                    flags.show_ends = true;
                    flags.show_tabs = true;
                    break;
                case 'b':
                    flags.number_nonblank = true;
                    break;
                case 'e':
                    flags.number = false;
                    flags.show_nonprinting = true;
                    flags.show_ends = true;
                    break;
                case 'E':
                    flags.show_ends = true;
                    break;
                case 'n':
                    flags.number = true;
                    break;
                case 's':
                    flags.squeeze_blank = true;
                    break;
                case 't':
                    flags.show_nonprinting = true;
                    flags.show_tabs = true;
                    break;
                case 'T':
                    flags.show_tabs = true;
                    break;
                case 'u':
                    break;
                case 'v':
                    flags.show_nonprinting = true;
                    break;
                default:
                    *error += 1;
                    (void)printf("%s: invalid option -- '%c'\n", APP_NAME, cur_arg[j]);
                    (void)printf("Try '%s --help' for more information.\n", APP_NAME);
                    break;
                }
            }
        } else if (cur_arg[0] == '-' && cur_arg[1] == '-') {
            if (strcmp(cur_arg, "--show-all") == 0) {
                flags.show_nonprinting = true;
                flags.show_ends = true;
                flags.show_tabs = true;
            } else if (strcmp(cur_arg, "--number-nonblank") == 0) {
                flags.number_nonblank = true;
            } else if (strcmp(cur_arg, "--show-ends") == 0) {
                flags.show_ends = true;
            } else if (strcmp(cur_arg, "--number") == 0) {
                flags.number = true;
            } else if (strcmp(cur_arg, "--squeeze-blank ") == 0) {
                flags.squeeze_blank = true;
            } else if (strcmp(cur_arg, "--show-tabs") == 0) {
                flags.show_tabs = true;
            } else if (strcmp(cur_arg, "--show-nonprinting") == 0) {
                flags.show_nonprinting = true;
            } else if (strcmp(cur_arg, "--help") == 0) {
                i = __INT_MAX__ - 1;
                flags.help = true;
                flags.number = false;
                flags.number_nonblank = false;
                flags.show_ends = false;
                flags.show_nonprinting = false;
                flags.show_tabs = false;
                flags.squeeze_blank = false;
                flags.version = false;
            } else if (strcmp(cur_arg, "--version") == 0) {
                i = __INT_MAX__ - 1;
                flags.help = false;
                flags.number = false;
                flags.number_nonblank = false;
                flags.show_ends = false;
                flags.show_nonprinting = false;
                flags.show_tabs = false;
                flags.squeeze_blank = false;
                flags.version = true;
            } else {
                *error += 1;
                (void)printf("%s: invalid option -- '%s'\n", APP_NAME, cur_arg);
                (void)printf("Try '%s --help' for more information.\n", APP_NAME);
            }
        }
    }
    return flags;
}


// ОЧЕНЬ СТРАШНЫЙ КОД
void print_flags(s21_cat_flags flags) {
    (void)printf("{\n");
    (void)printf("    \"help\": %s,\n", flags.help ? "true" : "false");
    (void)printf("    \"version\": %s,\n", flags.version ? "true" : "false");
    (void)printf("    \"number\": %s,\n", flags.number ? "true" : "false");
    (void)printf("    \"number_nonblank\": %s,\n", flags.number_nonblank ? "true" : "false");
    (void)printf("    \"show_ends\": %s,\n", flags.show_ends ? "true" : "false");
    (void)printf("    \"show_nonprinting\": %s,\n", flags.show_nonprinting ? "true" : "false");
    (void)printf("    \"show_tabs\": %s,\n", flags.show_tabs ? "true" : "false");
    (void)printf("    \"squeeze_blank\": %s\n", flags.squeeze_blank ? "true" : "false");
    (void)printf("}\n");
}