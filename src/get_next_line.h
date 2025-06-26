/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mderkaou <mderkaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:50:36 by mderkaou          #+#    #+#             */
/*   Updated: 2023/10/19 17:00:49 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

/*
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char				*get_next_line(int fd);
void				ft_read(int fd, t_list **stock);
void				add_buff(t_list **stock, char *buf, int readed);
void				extract_line(t_list *stock, char **line);
void				clean_stock(t_list **stock);
int					found_newline(t_list *stock);
t_list				*ft_lst_get_last(t_list *stock);
void				generate_line(char **line, t_list *stock);
void				free_stock(t_list *stock);

#endif
