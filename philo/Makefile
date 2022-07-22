NAME = philo

src = check_errors.c\
init.c\
main.c\
utils.c

obj = $(src:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -fsanitize=thread -g

$(NAME): $(obj)
	$(CC) $(CFLAGS) $(obj) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(obj)

fclean: clean
	rm -f $(NAME)

re: fclean all