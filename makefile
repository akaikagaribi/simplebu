all: s21_cat
s21_cat:
	gcc -Wall -Werror -Wextra -std=c11 s21_cat.c -o s21_cat
s21_grep:
	gcc -Wall -Werror -Wextra -std=c11 s21_grep.c -o s21_grep
clean:
	rm s21_cat