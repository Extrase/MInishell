# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thenry <thenry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 16:09:12 by thenry            #+#    #+#              #
#    Updated: 2023/11/08 20:19:43 by thenry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	src/main.c \
		src/error.c \
		src/tokenise_fl.c \
		src/tokenise_fl_utils.c \
		src/history.c \
		src/signal.c \
		src/create_cmds.c \
		src/create_cmds_bis.c \
		src/create_cmds_ter.c \
		src/print_all.c \
		src/tokenise_sl.c \
		src/tokenise_sl_utils.c \
		src/tokenise_sl_utils_bis.c \
		src/utils.c \
		src/clean_sl.c \
		src/clean_sl_utils.c \
		src/expansion.c \
		src/handle_quotes.c \
		src/handle_quotes_bis.c \
		src/handle_quotes_utils.c \
		src/free.c \
		src/exit_builtin.c \
		src/echo_builtin.c \
		src/get_env.c \
		src/env_builtin.c \
		src/export_builtin.c \
		src/pwd_builtin.c \
		src/unset_builtin.c \
		src/cd_builtin.c \
		src/cd_builtin_bis.c \
		src/exec/Xcution.c \
		src/exec/utils_exc.c \
		src/exec/clean_exec.c \
		src/exec/exec.c \
		src/exec/exec_builtin.c \
		src/exec/exec_tools.c \
		src/exec/ft_split_spec.c \
		src/exec/clean_exec2.c \
		src/exec/one_exec.c \
		src/exec/ft_here_doc.c \
		src/get_next_line.c \
		src/get_next_line_utils.c \
		src/exec/norm.c \
		src/exec/norm2.c

NAME	= 	minishell

OBJS	= 	${SRCS:.c=.o}

CFLAGS	= 	-Wall -Wextra -Werror -g

CC	= 	cc

LIBR	=	libft/libft.a

#VMINI	=	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --suppressions=/home/tibzer/42/minishell/minishell.supp

#VMINI	=	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --suppressions=/mnt/nfs/homes/thenry/rendu_42/minishell/minishell.supp

#VMINI	=	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --suppressions=/home/tibzer/42/minishell/minishell.supp

#rlleaks:	${NAME}
#		${VMINI} ./minishell

all:		${NAME}

.c.o:
		${CC} ${CFLAGS} -MMD -MP -c $< -o ${<:.c=.o}

-include ${SRCS:.c=.d}

${NAME}:	${OBJS}
		make -C libft
		${CC} ${CFLAGS} ${OBJS} ${LIBR} -lreadline -o ${NAME}
		
clean:		
		rm -rf ${OBJS}
		#rm -f draft/main.d
		rm -rf src/*.d
		rm -rf src/exec/*.d
		make -C libft clean

fclean:		clean
		rm -rf ${NAME}
		make -C libft fclean

re:		fclean all

.PHONY:		all re clean fclean
