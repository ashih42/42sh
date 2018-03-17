# Uncomment the TESTING_ENV variable to set it to testing environment.
# TESTING_ENV = 1;

NAME = 42sh
RM = /bin/rm -f
MKDIR = /bin/mkdir
CFLAGS = -Wall -Wextra -Werror 

SRCS_DIR = ./srcs/
INCLUDES = ./includes/
OBJS_DIR = ./objects/

FILES = built_ins.c \
		debug.c \
		dispatcher.c \
		envp.c \
		execute.c \
		ft_cd.c \
		ft_echo.c \
		ft_env.c \
		ft_exit.c \
		ft_history.c \
		ft_history_bang_exploder.c \
		ft_setenv.c \
		ft_unsetenv.c \
		globber.c \
		init.c \
		init_parse.c \
		listen.c \
		listen_utils.c \
		parse.c \
		path_utils.c \
		pipes.c \
		signal.c \
		split_argv.c \
		strip_argv.c \
		tab_autocomplete.c \
		term_utils.c \
		move_cursor.c
## Add main.c ^here^ when done testing

ifeq ($(TESTING_ENV),)
    FILES += main.c
else
    FILES += test_main.c
endif
CFILES = $(patsubst %, $(SRCS_DIR)%, $(FILES))
OFILES = $(patsubst %.c, $(OBJS_DIR)%.o, $(FILES))

#libft
LFT = ./libft/
LFT_LIB = $(addprefix $(LFT), ft.a)
LFT_INC = -I $(LFT)
LFT_LINK = -L $(LFT) -l ft

.PHONY: all clean fclean re

all: $(LFT_LIB) $(NAME)

$(OBJS_DIR):
	$(MKDIR) $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(OBJS_DIR)
	gcc $(CFLAGS) -c -I$(INCLUDES) $(LFT_INC) $< -o $@ -g

$(LFT_LIB):
	make -C $(LFT)

$(NAME): $(OFILES)
	gcc $(CFLAGS) $(OFILES) $(LFT_LINK) -o $(NAME)

clean:
	make -C $(LFT) clean
	$(RM) $(OFILES)

fclean: clean
	make -C $(LFT) fclean
	$(RM) $(NAME)

re: fclean all
