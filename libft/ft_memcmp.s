# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_memcmp.s                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apuel <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/15 13:51:12 by apuel             #+#    #+#              #
#    Updated: 2018/02/15 13:51:13 by apuel            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.global _ft_memcmp
_ft_memcmp:
	cld
	xor %eax, %eax
	mov %rdx, %rcx
	shr $3, %rcx
	jz byte_cmp
	repe cmpsq
	je byte_cmp
	sub $8, %rdi
	sub $8, %rsi
	mov $8, %rcx
	repe cmpsb
	jmp error
byte_cmp:
	and $7, %rdx
	jz ret
	mov %rdx, %rcx
	repe cmpsb
error:
	movzbl -1(%rdi), %eax
	movzbl -1(%rsi), %ecx
	sub %ecx, %eax
ret:
	ret
