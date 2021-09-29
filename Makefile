NAME		= 	minishell
CC			=	gcc
FLAGS	  	= #	-Werror -Wextra -Wall

UTILS		=	strtools_0.c strtools_4.c strtools_1.c strtools_2.c\
					split.c ft_itoa.c sf_malloc.c strtools_3.c

CMDS		= cmd_pwd.c cmd_unset.c cmd_exit.c cmd_echo.c\
				  cmd_env.c init_cmds.c	 cmd_cd.c cmd_export.c

HELPERS		= operations.c expand.c

VECTOR		= new_vector.c     vector_free.c       vector_resize.c\
				  vector_delete.c  vector_get.c        vector_set.c\
				  vector_find.c    vector_push_back.c vector_cpy.c

ROOT		=  errors.c  init.c  loop.c  minishell.c  n_pipes.c \
				   redirections.c  signals.c

PARSER      = pipe_fun.c redirections_errors.c space_fun.c space_fun_utils.c space_fun_utils__.c final_utils.c

SRC			=	$(ROOT:%.c=./src/%.c)\
					$(PARSER:%.c=./src/parser/%.c)\
					$(UTILS:%.c=./src/utils/%.c)\
					$(CMDS:%.c=./src/cmds/%.c)\
					$(VECTOR:%.c=./src/utils/Vector/%.c)\
					$(HELPERS:%.c=./src/helpers/%.c)

OBJ			=	$(SRC:.c=.o)
READLINE_FLAGS = -lreadline -L ~/.brew/opt/readline/lib  -I ~/.brew/opt/readline/include

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) ${FLAGS} -I include $(READLINE_FLAGS)  $(SRC)  -o $(NAME) -g  $(READLINE_FLAGS)

clean:
	@rm -rf ${OBJ}

fclean: clean
	@rm -f $(NAME)

re: fclean all
 