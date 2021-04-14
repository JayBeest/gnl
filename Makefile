test: get_next_line.c get_next_line_utils.c main.c
	clang $^ -Wall -Wextra -Werror -g -D MALLOC_DEBUG
