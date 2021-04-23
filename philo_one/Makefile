NAME		=	philo_one

SRCS		=	srcs/main.c \
				srcs/actions.c \
				srcs/actions2.c \
				srcs/time.c \
				srcs/init.c \
				srcs/utils.c \
				srcs/ft_atoul.c \
				srcs/parsing.c \
				srcs/parsing2.c \
				srcs/checks.c \
				srcs/prints.c

SRCS_PG		=	playground/main.c

OBJS		=	$(SRCS:.c=.o)
CC			=	clang
FLAGS		=	-Wall -Wextra -Werror -g -pthread
INC_PATH	=	-I./incs
COMPILE		=	$(CC) $(FLAGS) $(INC_PATH)

%.o : %.c
			$(CC) $(FLAGS) $(INC_PATH) -c $<  -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	${OBJS}
			$(COMPILE) $(OBJS) -o $(NAME)

clean:
			rm -f ${OBJS}

fclean:
			rm -f ${OBJS}
			rm -f ${NAME}

re:			fclean all

playground:	$(LIBS) $(SRCS_PG)
			$(COMPILE) $(SRCS_PG) -o srcs/playground/minishell_pg.out
			./srcs/playground/minishell_pg.out

test:		all
			sh ./test/test.sh

.PHONY:		clean fclean all re
