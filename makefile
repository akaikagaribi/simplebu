gcc = gcc -Wall -Werror -Wextra -std=c11

all: s21_cat s21_grep
s21_cat:
	$(gcc) s21_cat.c -o s21_cat
s21_grep:
	$(gcc) s21_grep.c -o s21_grep
clean:
	rm -f s21_cat
	rm -f s21_grep