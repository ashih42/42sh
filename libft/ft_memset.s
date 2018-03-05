# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_memset.s                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apuel <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/15 13:53:16 by apuel             #+#    #+#              #
#    Updated: 2018/02/15 13:53:17 by apuel            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.global _ft_memset
_ft_memset:
	mov %rdi, %r9
	cld
	mov %rdx, %rcx
	and $255, %rsi
	mov $0x0101010101010101, %rax
	mul %rsi
	mov %rcx, %rdx
	shr $3, %rcx
	rep stosq
	and $7, %rdx
	mov %rdx, %rcx
	rep stosb
	mov %r9, %rax
	ret
