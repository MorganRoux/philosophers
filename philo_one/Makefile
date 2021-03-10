NAME		=	philo_one

SRCS		=	srcs/main.c 

SRCS_PG		=	playground/main.c

OBJS		=	$(SRCS:.c=.o)
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
INC_PATH	=	-I./incs
COMPILE		=	$(CC) $(FLAGS) $(INC_PATH)

%.o : %.c	
			$(CC) $(FLAGS) $(INC_PATH) -c $<  -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	${OBJS}
			$(COMPILE) $(OBJS) -o $(NAME)
$(LIBFT):	
			make

clean:		
			make clean
			rm -f ${OBJS}

fclean:		
			make fclean
			rm -f ${OBJS}
			rm -f ${NAME}

re:			fclean all

playground:	$(LIBS) $(SRCS_PG)
			$(COMPILE) $(SRCS_PG) -o srcs/playground/minishell_pg.out
			./srcs/playground/minishell_pg.out

test:		all
			sh ./test/test.sh

.PHONY:		clean fclean all re 