NAME = ./libftprintf.a
SRC = $(wildcard *.c)
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I./includes
MAKE = make

all:$(NAME)

$(NAME): libft.a $(SRC:%.c=%.o)
		ar -rcsv $(NAME) $(SRC:%.c=%.o) ./libft/*.o

libft.a:
	$(MAKE) -C ./libft
	$(MAKE) bonus -C ./libft

clean:
	make clean -C ./libft
	$(RM)   $(SRC:%.c=%.o)

fclean: clean
		make fclean -C ./libft
		$(RM)   $(NAME)

re: fclean  $(NAME)

so: $(SRC:%.c=%.o)
	gcc -shared -o libft.so $(SRC:%.c:=%.o)

.PHONY:         all clean fclean bonus