/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:18:40 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/01 10:28:02 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* This functions checks the length of the token until a delimiter is found */
int	token_len(char *str)
{
	int	i;

	i = 1;
	if (str[1] && ft_isdelimiter(str))
		i = ft_isdelimiter(str);
	else if (!str[1] && str[0] == ')')
		i = ft_isdelimiter(str);
	else
		i = check_text(str);
	return (i);
}

/* Function to skip characters between quotes
or to skip characters until a quotation mark is found */
int	skip_quotes(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '\'' && str[0] != '\"')
	{
		while (str[i + 1] && str[i] != '\'' && str[i] != '\"')
			i++;
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			i--;
	}
	else
	{
		while (str[++i] && str[i] != str[0])
			continue ;
	}
	return (i);
}
