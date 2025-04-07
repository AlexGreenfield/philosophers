NAME = philo

# Compiling libs and flags
LIBS = -pthread

# Mandatory sources and objects
SRCS = philo.c \
	check_args.c \
	utils_routine.c \
	utils_args.c \
	init_program.c \
	init_philos.c \
	init_routines.c \
	routine_waiter.c \
	routine_philos.c \
	routine_philos_eat.c \
	free_structs.c \

OBJS = $(SRCS:.c=.o)

# Compilation
CC = cc
CFLAGS = -Werror -Wextra -Wall -g

# Colors for Makefile output
RED    = \033[0;31m
GREEN  = \033[0;32m
YELLOW = \033[0;33m
BLUE   = \033[0;34m
RESET  = \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "\n\n$(BLUE)Linking object files and libraries...$(RESET)\n\n"
	cc $(OBJS) -o $(NAME) $(LIBS)
	@echo "\n\n$(GREEN)Build complete!$(RESET)\n\n"

%.o: %.c
	@echo "\n\n$(BLUE)Compiling $<...$(RESET)\n\n"
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@echo "\n\n$(RED)Cleaning object files...$(RESET)\n\n"
	@rm -f $(OBJS)

fclean: clean
	@echo "\n\n$(RED)Cleaning all...$(RESET)\n\n"
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re
