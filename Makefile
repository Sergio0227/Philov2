# Define variables
SRC =	src/main.c				\
		src/gc.c 				\
		src/utils.c 			\
		src/time.c 				\
		src/intro.c 			\
		src/simulation.c 		\
		src/safe_get_and_set.c 	


OBJS = ${SRC:.c=.o}
NAME = philo
CC = cc
CFLAGS = -Werror -Wextra -Wall
RM = rm -f

# Define colors
DEF_COLOR = \033[0;39m
ORANGE = \033[0;33m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[1;92m
YELLOW = \033[1;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: ${NAME}

${NAME}: ${OBJS}
	@echo "$(ORANGE)[Philosophers]:$(DEF_COLOR) Linking object files to create executable $(GREEN)${NAME}$(DEF_COLOR)"
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "$(ORANGE)[Philosophers]:$(DEF_COLOR) exec file $(GREEN)=> Created!$(DEF_COLOR)"

%.o: %.c
	@echo "Compiling $< with flags \"${CFLAGS}\""
	@${CC} ${CFLAGS} -c $< -o $@
	@echo "$(GREEN)Compilation of $< success$(DEF_COLOR)"

clean:
	@${RM} ${OBJS}
	@echo -n "$(CYAN)[Philosophers]:$(DEF_COLOR) object files$(RED) \t => Removed!$(DEF_COLOR)\n";

fclean: clean
	@echo -n "$(CYAN)[Philosophers]:$(DEF_COLOR) exec. files$(RED)  => Removed!$(DEF_COLOR)\n";
	@${RM} ${NAME};


re: fclean all

.PHONY: all clean fclean re
