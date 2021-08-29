
.PHONEY: all clean fclean re bonus

NAME			= 	minishell
CC				=	gcc
FLAGS	  		= 	#-Werror -Wextra -Wall

UTILS			=	strtools_0.c strtools_4.c strtools_1.c strtools_2.c\
					split.c ft_itoa.c sf_malloc.c strtools_3.c

CMDS			= cmd_pwd.c cmd_unset.c cmd_exit.c cmd_echo.c\
				  cmd_env.c init_cmds.c	 cmd_cd.c cmd_export.c

HELPERS			= operations.c

VECTOR			= new_vector.c     vector_free.c       vector_resize.c\
				  vector_delete.c  vector_get.c        vector_set.c\
				  vector_find.c    vector_push_back.c vector_cpy.c

ROOT			=  errors.c  init.c  loop.c  minishell.c  n_pipes.c \
				   redirections.c  signals.c

PARSER          = pipe_fun.c redirections_errors.c space_fun.c

SRC				=	$(ROOT:%.c=./src/%.c)\
					$(PARSER:%.c=./src/parser/%.c)\
					$(UTILS:%.c=./src/utils/%.c)\
					$(CMDS:%.c=./src/cmds/%.c)\
					$(VECTOR:%.c=./src/utils/Vector/%.c)\
					$(HELPERS:%.c=./src/helpers/%.c)
					# helpers/operations.c

OBJ				=	$(SRC:.c=.o)
DBG_FLAGS		=  -g -fsanitize=address
READLINE_FLAGS  = -L/usr/include -lreadline

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) ${FLAGS} -I include $(READLINE_FLAGS)  $(SRC)  -lreadline  -o $(NAME) -g
	@rm -rf *.o

san :
	@$(CC) $(DBG_FLAGS) $(READLINE_FLAGS) -I include -lncurses  $(SRC) -lreadline  -o $(NAME) 
	@rm -rf *.o
	
$(OBJ): $(SRC)
	@$(COMPILE)

clean:
	@rm -rf *.o

fclean: clean
	@rm -f $(NAME)
	@rm -rf *.o

re: fclean all

bu: fclean
	@bash git_bu.sh
