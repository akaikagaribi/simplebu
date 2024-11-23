#include "s21_grep.h"

char get_line(FILE* file, char* linebuf);
void print_args(s21_grep_args args);

int main(int argc, char* argv[]) {
    int error = 0;
    s21_grep_args args = {};
    (void)parse_args(argc, argv, &args, &error);
    (void)print_args(args);
    return error;
    regex_t regex;
    int reti;
    reti = regcomp(&regex, argv[1], 0);
    FILE* file = NULL;
    if (argc > 2) {
        file = fopen(argv[2], "r");
    } else {
        file = stdin;
    }
    char lspci[LINE_SIZE] = {};
    int lineno = 0;
    (void)get_line(file, lspci);
    for (int i = 0; lspci[0] != -1; i++) {
        lineno++;
        if (lspci[0] != 0 && lspci[0] != -1) {
            reti = regexec(&regex, lspci, 0, NULL, 0);
            if (!reti) {
                // -n
                // (void)printf("%d:%s\n", lineno, lspci);
                (void)printf("%s\n", lspci);
            }
        }
        (void)get_line(file, lspci);
    }
    regfree(&regex);
    (void)fclose(file);
    return error;
}

char get_line(FILE* file, char* linebuf) {
    char ch = getc(file);
    int i = 0;
    while (i < LINE_SIZE && ch != 10 && ch != -1) {
        linebuf[i] = ch;
        ch = getc(file);
        i++;
    }
    if (i == 0 && ch == -1) {
        linebuf[i] = -1;
    } else {
        linebuf[i] = 0;
    }
    return ch;
}

int add_str_to_str(char* first, char* second, bool is_file) {
    int err = 0;
    size_t limit = LINE_SIZE - strlen(first);
    if (limit - strlen(second) == 0) {
        (void)printf("%s: Buffer overflow\n", APP_NAME);
        err += 1;
    }
    if (err == 0) {
        if (strcmp(first, "") == 0) {
            (void)strncat(first, second, limit);
        } else {
            is_file ? (void)strncat(first, "|", 3) : (void)strncat(first, "\\|", 3);
            (void)strncat(first, second, limit - 1);
        }
    }
    return err;
}

int asts_from_file(char* string, char* filename) {
    int err = 0;
    FILE* regexfile = fopen(filename, "r");
    if (regexfile == NULL) {
        (void)printf("%s: %s: No such file or directory\n", APP_NAME, filename);
        err += 1;
    } else {
        char rline[LINE_SIZE] = {};
        (void)get_line(regexfile, rline);
        for (int j = 0; rline[0] != -1 && err == 0; j++) {
            if (rline[0] != 0 && rline[0] != -1) {
                err = add_str_to_str(string, rline, false);
            }
            (void)get_line(regexfile, rline);
        }
        (void)fclose(regexfile);
    }
    return err;
}

void parse_args(int argc, char* argv[], s21_grep_args* args, int* error) {
    if (argc == 1) {
        args->help = true;
        *error += 1;
    }
    if (*error == 0 && argc > 1) {
        int ec = 0;
        int fc = 0;
        for (int i = 1; i < argc && *error == 0; i++) {
            if (argv[i][0] == '-') {
                if (argv[i][1] == 'e') {
                    if (argv[i][2] == '\0') {
                        *error = add_str_to_str(args->regex, argv[i + 1], false);
                        i++;
                    } else {
                        *error = add_str_to_str(args->regex, argv[i] + 2, false);
                    }
                    ec++;
                } else if (argv[i][1] == 'f') {
                    if (argv[i][2] == '\0') {
                        *error = asts_from_file(args->regex, argv[i + 1]);
                        i++;
                    } else {
                        *error = asts_from_file(args->regex, argv[i] + 2);
                    }
                } else {
                    for (int j = 1; argv[i][j] != '\0' && *error == 0; j++) {
                        if (argv[i][j] == 'i') {
                            args->case_insensetive = true;
                        } else if (argv[i][j] == 'v') {
                            args->invert = true;
                        } else if (argv[i][j] == 'c') {
                            args->only_count = true;
                        } else if (argv[i][j] == 'l') {
                            args->only_filenames = true;
                        } else if (argv[i][j] == 'n') {
                            args->number = true;
                        } else if (argv[i][j] == 'h') {
                            args->no_filenames = true;
                        } else if (argv[i][j] == 's') {
                            args->supress_errors = true;
                        } else if (argv[i][j] == 'o') {
                            args->only_matches = true;
                        } else {
                            *error += 1;
                            (void)printf("%s: invalid option -- '%c'\n", APP_NAME,
                                        argv[i][j]);
                            (void)printf("Try '%s --help' for more information.\n",
                                        APP_NAME);
                        }
                    }
                }
            }
        }
        for (int i = 1; i < argc && *error == 0; i++) {
            if (argv[i][0] != '-' && strcmp(argv[i - 1], "-e") != 0 && strcmp(argv[i - 1], "-f") != 0) {
                if (ec == 0) {
                    *error = add_str_to_str(args->regex, argv[i], false);
                    ec++;
                } else {
                    *error = add_str_to_str(args->filenames, argv[i], true);
                    fc++;
                }
            }
        }
        if (strcmp(args->filenames, "") == 0) {
            (void)strncpy(args->filenames, "-", 2);
            fc++;
        }
        if (fc < 2) {
            args->no_filenames = true;
        }
    }
}

void print_args(s21_grep_args args) {
    (void)printf("{\n");
    (void)printf("    \"help\": %s,\n", args.help ? "true" : "false");
    (void)printf("    \"version\": %s,\n", args.version ? "true" : "false");
    (void)printf("    \"case_insensetive\": %s,\n", args.case_insensetive ? "true" : "false");
    (void)printf("    \"invert\": %s,\n", args.invert ? "true" : "false");
    (void)printf("    \"only_count\": %s,\n", args.only_count ? "true" : "false");
    (void)printf("    \"only_filenames\": %s,\n", args.only_filenames ? "true" : "false");
    (void)printf("    \"number\": %s,\n", args.number ? "true" : "false");
    (void)printf("    \"no_filenames\": %s,\n", args.no_filenames ? "true" : "false");
    (void)printf("    \"supress_errors\": %s,\n", args.supress_errors ? "true" : "false");
    (void)printf("    \"only_matches\": %s,\n", args.only_matches ? "true" : "false");
    (void)printf("    \"filenames\": \"%s\",\n", args.filenames);
    (void)printf("    \"regex\": \"%s\",\n", args.regex);
    (void)printf("}\n");
}