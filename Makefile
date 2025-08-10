CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread
SRCS = philosophers.c utils.c philo_init.c routine.c print_data.c philo_utils.c
OBJS = philosophers.o philo_init.o routine.o utils.o print_data.o philo_utils.o forks.o
NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all