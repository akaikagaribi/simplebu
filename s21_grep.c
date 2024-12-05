#include "s21_grep.h"

void print_args(s21_grep_args args);

int main(int argc, char* argv[]) {
    int error = 0;
    s21_grep_args args = {};
    (void)parse_args(argc, argv, &args, &error);
    // (void)print_args(args);
    if (error == 0) {
        if (args.help) {
            (void)print_help();
        } else if (args.version) {
            (void)print_version();
        } else {
            (void)parse_files(args, &error);
        }
    }
    return error;
}

void parse_files(s21_grep_args args, int* error) {
    regex_t regex;
    int cflags = args.case_insensetive ? REG_ICASE : 0;
    int reti = regcomp(&regex, args.regex, cflags);
    if (reti != 0) {
        (void)printf("%s: invalid regex", APP_NAME);
        *error += 1;
    }
    char filenames[LINE_SIZE] = {};
    (void)strcpy(filenames, args.filenames);
    char* filename;
    filename = strtok(filenames, "|");
    while (filename != NULL && *error == 0) {
        (void)grep_file(filename, regex, args, error);
        filename = strtok(NULL, "|");
    }
    (void)regfree(&regex);
}

void grep_file(char* filename, regex_t regex, s21_grep_args args, int* error) {
    FILE* file = strcmp(filename, "-") == 0 ? stdin : fopen(filename, "r");
    if (file != NULL) {
        int lineno = 0;
        int matches = 0;
        char line[LINE_SIZE] = {};
        char* linetoregex = line;
        char lc = get_line(file, line, true);
        while (line[0] != 0 && line[0] != -1) {
            lineno += 1;
            regmatch_t pmatch[1];
            int reti = regexec(&regex, linetoregex, 1, pmatch, 0);
            if ((!args.invert && reti == 0) || (args.invert && reti != 0)) {
                if (!args.only_filenames && !args.only_count) {
                    if (args.only_matches) {
                        while (reti == 0) {
                            regoff_t len = pmatch[0].rm_eo - pmatch[0].rm_so;
                            if (!args.no_filenames) {
                                (void)printf("%s:", filename);
                            }
                            if (args.number) {
                                (void)printf("%d:", lineno);
                            }
                            (void)printf("%.*s\n", len,
                                         linetoregex + pmatch[0].rm_so);
                            linetoregex += pmatch[0].rm_eo;
                            reti = regexec(&regex, linetoregex, 1, pmatch, 0);
                        }
                    } else {
                        if (!args.no_filenames) {
                            (void)printf("%s:", filename);
                        }
                        if (args.number) {
                            (void)printf("%d:", lineno);
                        }
                        (void)printf("%s", line);
                        if (lc != '\n') {
                            (void)printf("\n");
                        }
                    }
                } else {
                    matches += 1;
                }
            }
            lc = get_line(file, line, true);
            linetoregex = line;
        }
        if (args.only_filenames) {
            if (matches > 0) {
                (void)printf("%s\n", filename);
            }
        } else if (args.only_count) {
            if (!args.no_filenames) {
                (void)printf("%s:", filename);
            }
            (void)printf("%d\n", matches);
        }
    } else {
        if (!args.supress_errors) {
            (void)printf("%s: %s: No such file or directory\n", APP_NAME,
                         filename);
        }
    }
    if (*error == 0 && file != NULL) {
        (void)fclose(file);
    }
}

char get_line(FILE* file, char* linebuf, bool keep_newline) {
    char ch = getc(file);
    int i = 0;
    while (i < LINE_SIZE && ch != 10 && ch != -1) {
        linebuf[i] = ch;
        ch = getc(file);
        i++;
    }
    if (keep_newline && ch == 10) {
        linebuf[i] = ch;
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
            is_file ? (void)strncat(first, "|", 3)
                    : (void)strncat(first, "\\|", 3);
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
        (void)get_line(regexfile, rline, false);
        for (int j = 0; rline[0] != -1 && err == 0; j++) {
            if (rline[0] != 0 && rline[0] != -1) {
                err = add_str_to_str(string, rline, false);
            }
            (void)get_line(regexfile, rline, false);
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
                        *error =
                            add_str_to_str(args->regex, argv[i + 1], false);
                        i++;
                    } else {
                        *error =
                            add_str_to_str(args->regex, argv[i] + 2, false);
                    }
                    ec++;
                } else if (argv[i][1] == 'f') {
                    if (argv[i][2] == '\0') {
                        *error = asts_from_file(args->regex, argv[i + 1]);
                        i++;
                    } else {
                        *error = asts_from_file(args->regex, argv[i] + 2);
                    }
                    ec++;
                } else if (argv[i][1] == '-') {
                    if (strcmp(argv[i], "--help") == 0 ||
                        strcmp(argv[i], "--version") == 0) {
                        args->help =
                            strcmp(argv[i], "--help") == 0 ? true : false;
                        args->version =
                            strcmp(argv[i], "--version") == 0 ? true : false;
                        i = argc;
                    } else {
                        *error += 1;
                        (void)printf("%s: invalid option -- '%s'\n", APP_NAME,
                                     argv[i]);
                        (void)printf("Try '%s --help' for more information.\n",
                                     APP_NAME);
                    }
                } else {
                    for (int j = 1; argv[i][j] != '\0' && *error == 0; j++) {
                        if (argv[i][j] == 'i') {  // DONE
                            args->case_insensetive = true;
                        } else if (argv[i][j] == 'v') {  // DONE
                            args->invert = true;
                        } else if (argv[i][j] == 'l') {  // DONE
                            args->only_filenames = true;
                        } else if (argv[i][j] == 'c') {  // DONE
                            args->only_count = true;
                        } else if (argv[i][j] == 'n') {  // DONE
                            args->number = true;
                        } else if (argv[i][j] == 'h') {  // DONE
                            args->no_filenames = true;
                        } else if (argv[i][j] == 's') {  // DONE
                            args->supress_errors = true;
                        } else if (argv[i][j] == 'o') {  // DONE
                            args->only_matches = true;
                        } else {
                            *error += 1;
                            (void)printf("%s: invalid option -- '%c'\n",
                                         APP_NAME, argv[i][j]);
                            (void)printf(
                                "Try '%s --help' for more information.\n",
                                APP_NAME);
                        }
                    }
                }
            }
        }
        for (int i = 1; i < argc && *error == 0; i++) {
            if (argv[i][0] != '-' && strcmp(argv[i - 1], "-e") != 0 &&
                strcmp(argv[i - 1], "-f") != 0) {
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

void print_help() {
    (void)printf("Usage: %s [PARAMS]... [FILE]...\n", APP_NAME);
}

void print_version() {
    (void)printf("%s (42 simplebashutils) %s\n", APP_NAME, APP_VERSION);
}

void print_args(s21_grep_args args) {
    (void)printf("{\n");
    (void)printf("    \"help\": %s,\n", args.help ? "true" : "false");
    (void)printf("    \"version\": %s,\n", args.version ? "true" : "false");
    (void)printf("    \"case_insensetive\": %s,\n",
                 args.case_insensetive ? "true" : "false");
    (void)printf("    \"invert\": %s,\n", args.invert ? "true" : "false");
    (void)printf("    \"only_count\": %s,\n",
                 args.only_count ? "true" : "false");
    (void)printf("    \"only_filenames\": %s,\n",
                 args.only_filenames ? "true" : "false");
    (void)printf("    \"number\": %s,\n", args.number ? "true" : "false");
    (void)printf("    \"no_filenames\": %s,\n",
                 args.no_filenames ? "true" : "false");
    (void)printf("    \"supress_errors\": %s,\n",
                 args.supress_errors ? "true" : "false");
    (void)printf("    \"only_matches\": %s,\n",
                 args.only_matches ? "true" : "false");
    (void)printf("    \"filenames\": \"%s\",\n", args.filenames);
    (void)printf("    \"regex\": \"%s\",\n", args.regex);
    (void)printf("}\n");
}