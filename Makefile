# Uncomment the TESTING_ENV variable to set it to testing environment.
# TESTING_ENV = 1;

NAME = 42sh
RM = /bin/rm -f
MKDIR = /bin/mkdir
CFLAGZ = -Wall -Wextra -Werror 
# ^ mispelled CFLAGS :>

SRCS_DIR = ./srcs/
INCLUDES = ./includes/
OBJS_DIR = ./objects/

FILES = init.c listen.c parse.c dispatcher.c envp.c split_argv.c ft_cd.c \
ft_echo.c ft_exit.c ft_setenv.c ft_unsetenv.c ft_env.c signal.c ft_history.c \
str_explode.c ft_history_bang_exploder.c debug.c redir.c ft_3d_parser.c

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
