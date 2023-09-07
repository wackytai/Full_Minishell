/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:36:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/07 15:02:41 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* Function to put tokens list head at the begining */
int	reset_lst(t_data *data, t_tokens *token)
{
	while (token->prev)
		token = token->prev;
	data->tokens = token;
	return (1);
}

/* This function checks if the token order received is allowed */
int	check_token_sequence(t_tokens *token)
{
	int	flag;

	flag = 0;
	if (!token->prev && (token->type == 2 || token->type == 3))
		flag = 1;
	while (token && flag == 0)
	{
		if (!token->next && token->type < 4)
		{
			flag = 2;
			break ;
		}
		else if ((token->type < 3 && token->next->type == token->type)
			|| (token->type < 2 && token->next->type <= 2))
			flag = 1;
		token = token->next;
	}
	if (!flag)
		return (0);
	if (flag == 1)
		print_message(0, token->content, 0);
	if (flag == 2)
		print_message(0, "newline", 0);
	return (set_exit_code(2, true));
}

/* Function to spot '*', expand it and add expasions to token list */
int	check_wildcards(t_tokens **t)
{
	int				i;
	int				wdc;
	DIR				*dirp;

	i = -1;
	wdc = expand_wildcards((*t)->content);
	if (!wdc)
		return (0);
	else if (wdc < 0)
		return (1);
	while ((*t)->content[++i] && (*t)->content[i] != '\''
		&& (*t)->content[i] != '\"')
		continue ;
	if (i < (int)ft_strlen((*t)->content))
		return (0);
	dirp = opendir(".");
	if (!dirp)
		return (set_exit_code(1, true));
	if (find_wildcard(dirp, t) && !closedir(dirp))
		return (set_exit_code(1, true));
	if (closedir(dirp))
		return (set_exit_code(1, true));
	return (0);
}

/* Function to get the variable name
and increment the counter according to its size */
char	*expand_dollar(char *str, int *i, t_tokens *env)
{
	char	*var;
	char	*exit_code;
	int		index;

	index = *i;
	var = separate_var(&str[index]);
	if (!ft_strcmp(var, "$"))
		*i += 1;
	else
		*i += ft_strlen(var) + 1;
	if (!ft_strcmp(var, "?"))
	{
		exit_code = ft_itoa(set_exit_code(0, false));
		free(var);
		var = exit_code;
	}
	else if (ft_strcmp(var, "$"))
		var = search_var(var, env);
	return (var);
}
