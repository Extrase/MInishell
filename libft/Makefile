# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thenry <thenry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 14:55:42 by thenry            #+#    #+#              #
#    Updated: 2022/11/21 11:47:10 by thenry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_atoi.c

BONUS	=	ft_lstnew.c ft_lstlast.c ft_lstadd_front.c ft_lstsize.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

INC	=	libft.h

NAME	=	libft.a

OBJS	=	${SRCS:.c=.o}

BONUS_OBJS =	${BONUS:.c=.o}

CFLAGS	=	-Wall -Wextra -Werror

CC	=	cc

all:		${NAME}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
		ar rcs ${NAME} ${OBJS} ${INC}

bonus:		${OBJS} ${BONUS_OBJS}
		ar rcs ${NAME} ${OBJS} ${BONUS_OBJS} ${INC}

clean:
		rm -f ${OBJS} ${BONUS_OBJS}

fclean:		clean
		rm -f ${NAME}

re:		fclean all

.PHONY:		bonus all clean fclean re
