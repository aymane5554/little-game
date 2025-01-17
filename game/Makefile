CC = cc 
CFLAGS = #-Wall -Wextra -Werror
NAME = exe
SOURCES = get_next_line.c get_next_line_utils.c tests.c path_to_coins.c utils.c main.c movement.c enemy.c ending.c counter.c animation.c init.c display_moves.c errors.c 
OBJS = $(SOURCES:%.c=%.o)
all : $(NAME)

$(NAME): $(OBJS) $(SHARED_OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L mlx -lmlx -lXext -lX11 -lm -o $(NAME)

get_next_line%.o : get_next_line%.c get_next_line.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o : %.c header.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
