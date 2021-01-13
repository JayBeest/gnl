NAME = gnl

SRC = main.c get_next_line.c get_next_line_utils.c

HEADER_FILES = get_next_line.h

O_FILES = $(SRC:.o=.c)

all: $(NAME)

$(NAME): $(O_FILES)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADER_FILES)
	@echo Compiling $@
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(O_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re