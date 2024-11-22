#include "s21_grep.h"

char get_line(FILE* file, char* linebuf);
void intprint(char* string);

int main(int argc, char* argv[]) {
    int error = 0;
    regex_t regex;
    int reti;
    reti = regcomp(&regex, argv[1], 0);
    FILE* file = NULL;
    if (argc > 2) {
        file = fopen(argv[2], "r");
    } else {
        file = stdin;
    }
    char lspci[4096] = {};
    int lineno = 0;
    (void)get_line(file, lspci);
    for (int i = 0; lspci[0] != -1; i++) {
        lineno++;
        if (lspci[0] != 0 and lspci[0] != -1) {
            reti = regexec(&regex, lspci, 0, NULL, 0);
            if (!reti) {
                // -n
                // (void)printf("%d:%s\n", lineno, lspci);
                (void)printf("%s\n", lspci);
            }
        }
        (void)get_line(file, lspci);
    }
    (void)fclose(file);
    return error;
}

char get_line(FILE* file, char* linebuf) {
    char ch = getc(file);
    int i = 0;
    while (i < 4096 and ch != 10 and ch != -1) {
        linebuf[i] = ch;
        ch = getc(file);
        i++;
    }
    if (i == 0 and ch == -1) {
        linebuf[i] = -1;
    } else {
        linebuf[i] = 0;
    }
    return ch;
}

void intprint(char* string) {
    int i = 0;
    while (string[i] != -1) {
        (void)putc(string[i], stdout);
        i++;
    }
    (void)putc(10, stdout);
}