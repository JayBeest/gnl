test: get_next_line.c get_next_line_utils.c main.c
	clang $^ -Wall -Wextra -Werror -g -fsanitize=address #-D MALLOC_DEBUG
