#include "s21_cat.h"

int main() {
    FILE* file = fopen("test1.txt", "r");
    int ch = getc(file);
    while (ch >= 0) {
        (void)putc(ch, stdout);
        ch = getc(file);
    }
    return 0;
}