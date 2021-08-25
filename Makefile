NAME = libgnl.a
HEADER_FILES = get_next_line.h
SRCS =	get_next_line.c \
		get_next_line_utils.c
O_FILES = $(SRCS:%.c=%.o)
CFLAGS = -g -Wall -Wextra -Werror #-fsanitize=address
CC = clang

all: $(NAME)

$(NAME): $(O_FILES)
	$(AR) -r $@ $^

%.o: %.c $(HEADER_FILES)
	$(CC) -o $@ $< -c $(CFLAGS)

test: get_next_line.c get_next_line_utils.c main.c
	clang $^ -Wall -Wextra -Werror -g #-D MALLOC_DEBUG

clean:
	rm $(O_FILES)

fclean: clean
	rm $(NAME)

re: fclean all
