/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenise_sl_utils_bis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thenry <thenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:22:55 by thenry            #+#    #+#             */
/*   Updated: 2023/11/04 14:24:38 by thenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator_type(int type)
{
	return (type == FTSPACE || type == FTTAB);
}

int	is_special_type(int type)
{
	return (type == SQUOTE || type == DQUOTE || type == DOLLAR || type == PIPE
		|| type == REDIRIN || type == REDIROUT);
}

int	is_separator_or_operator(int type, char c)
{
	return (type == FTSPACE || type == FTTAB || ft_is_op(c));
}
