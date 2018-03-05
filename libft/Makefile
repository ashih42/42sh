# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apuel <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/06 11:59:56 by apuel             #+#    #+#              #
#    Updated: 2017/12/05 17:59:51 by apuel            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:=	gcc
CCFLAGS		:=	-Wall -Wextra -Werror -I. -c

NAME		:=	libft.a

LIBSRCFILES	:=	ft_atoi.c ft_bzero.s ft_prime.c ft_isalnum.c ft_isspace.c\
				ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c\
				ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c\
				ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.s\
				ft_memcpy.s ft_memdel.c ft_memmove.c ft_memset.s ft_pow.c\
				ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_lstadd_back.c\
				ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c\
				ft_putstr_fd.c ft_sqrt.c ft_strcat.c ft_strchr.c ft_strclr.c\
				ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c\
				ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c\
				ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c\
				ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c\
				ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c\
				ft_toupper.c ft_sqrt.c ft_sqrt_r.c ft_nbrlen_base.c\
				ft_putnbr_base.c ft_putwchar.c ft_putwstr.c ft_wstrlen.c\
				ft_putstrn.c ft_putwstrn.c ft_print_strarray.c ft_getfilesize.c\
				ft_readfile.c ft_readstdin.c ft_rand64.c ft_atoi_base.c\
				ft_printf.c
FT_PRINTF	:=	ft_printf_writer.c ft_printf_color.c ft_printf_nbr.c\
				ft_printf_strings.c ft_printf_float.c ft_printf_font.c\
				ft_printf_float_cmp.c ft_printf_float_hex.c

SRCFILES	:=	$(LIBSRCFILES) $(addprefix ft_printf/, $(FT_PRINTF))
OFILES		:=	$(notdir $(SRCFILES:.c=.o))
OFILES		:=	$(OFILES:.s=.o)

all: $(NAME)

$(NAME):
		$(CC) $(CCFLAGS) $(SRCFILES)
		ar rc $(NAME) $(OFILES)

clean:
		rm -f $(OFILES)

fclean: clean
		rm -f $(NAME)

re: fclean all
