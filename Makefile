NAME = 42sh
RM = /bin/rm -f
MKDIR = /bin/mkdir
CFLAGS = -Wall -Wextra -Werror 

SRCS_DIR = ./srcs/
INCLUDES = ./includes/
OBJS_DIR = ./objects/

FILES = built_ins.c \
		dispatcher.c \
		envp.c \
		execute.c \
		ft_cd.c \
		ft_echo.c \
		ft_env.c \
		ft_exit.c \
		ft_export.c \
		ft_glob.c \
		ft_history.c \
		ft_history_bang_exploder.c \
		ft_setenv.c \
		ft_super_factory.c \
		ft_unset.c \
		ft_unsetenv.c \
		glob_utils.c \
		init.c \
		listen.c \
		listen_utils.c \
		main.c \
		match.c \
		move_cursor.c \
		parse.c \
		path_utils.c \
		pipes.c \
		signal.c \
		split_argv.c \
		split_dirs.c \
		strip_argv.c \
		tab_ac_utils.c \
		tab_ac_utils2.c \
		tab_autocomplete.c \
		term_utils.c

CFILES = $(patsubst %, $(SRCS_DIR)%, $(FILES))
OFILES = $(patsubst %.c, $(OBJS_DIR)%.o, $(FILES))

LFT = ./libft/
LFT_LIB = $(addprefix $(LFT), ft.a)
LFT_INC = -I $(LFT)
LFT_LINK = -L $(LFT) -l ft

.PHONY: all clean fclean re

all: $(LFT_LIB) $(NAME)

$(OBJS_DIR):
	$(MKDIR) $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(OBJS_DIR)
	gcc $(CFLAGS) -c -I$(INCLUDES) $(LFT_INC) $< -o $@

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
