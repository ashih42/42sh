# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_memcpy.s                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apuel <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/15 13:46:04 by apuel             #+#    #+#              #
#    Updated: 2018/02/15 13:46:06 by apuel            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.global _ft_memcpy
_ft_memcpy:
	mov %rdi, %rax
	cld
	mov %rdx, %rcx
	shr $3, %rcx
	rep movsq
	and $7, %rdx
	mov %rdx, %rcx
	rep movsb
	ret
