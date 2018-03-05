# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_bzero.s                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apuel <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/15 13:44:42 by apuel             #+#    #+#              #
#    Updated: 2018/02/15 13:44:45 by apuel            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.global _ft_bzero
_ft_bzero:
	cld
	xor %rax, %rax
	mov %rsi, %rcx
	shr $3, %rcx
	rep stosq
	and $7, %rsi
	mov %rsi, %rcx
	rep stosb
	ret