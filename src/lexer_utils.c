/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:07:03 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/18 08:27:00 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* This function checks for forbidden sequence of characters */
int	ft_isforbidden_char(char *str)
{
	if (str[0] && (str[0] == '\\' || str[0] == '`' || str[0] == '['
			|| str[0] == ']' || str[0] == ';' || str[0] == '#'
			|| str[0] == '{' || str[0] == '}'))
	{
		forbidden_print(2, str);
		return (set_exit_code(1, true));
	}
	if (str[0] && ((str[0] == '(' && str[1] == ')')
			|| (str[0] == '<' && str[1] == '&')
			|| (str[0] == '>' && str[1] == '&')
			|| (str[0] == '&' && str[1] == '>')
			|| (str[0] == '$' && str[1] == '(')
			|| (str[0] == ')' && str[1] == '$')
			|| (str[0] == '[' && str[1] == ']')
			|| (str[0] == '&' && str[1] == '&')
			|| (str[0] == '|' && str[1] == '|')))
	{
		forbidden_print(1, &str[0]);
		return (set_exit_code(1, true));
	}
	return (0);
}

/* Function to check if character is a delimiter */
int	ft_isdelimiter(char *str)
{
	int	flag;

	flag = 0;
	if (str[0] == '(' || str[0] == ')')
		flag = 1;
	else if (str[1] && (str[0] == '<' || str[0] == '>' || str[0] == '|')
		&& str[1] != str[0])
		flag = 1;
	else if (str[1] && (str[0] == '<' || str[0] == '>' || str[0] == '|'
			|| str[0] == '&') && str[1] == str[0])
		flag = 2;
	return (flag);
}

/* This function checks if the token has any forbidden characters 
and handles quotations marks as intended */
int	check_text(char *str)
{
	int	j;
	int	k;

	j = 0;
	while (str[j] && !ft_isdelimiter(&str[j]) && !ft_isspace(str[j]))
	{
		if (ft_isforbidden_char(&str[j]))
			return (0);
		if (str[j] == '\'' || str[j] == '\"')
		{
			k = skip_quotes(&str[j]);
			if (!str[k] || (k == 1 && (str[j] == '\'' || str[j] == '\"')
					&& !str[k]))
			{
				printf("unexpected EOF while looking for matching `%c'\n",
					str[j]);
				set_exit_code(1, true);
				return (0);
			}
			j += k;
		}
		j++;
	}
	return (j);
}

/* Function to separate tokens into cathegories:
	0 = simple redirection
	1 = double redirection (here_doc)
	2 = pipe
	3 = operators
	4 = limiter for here_doc
	5 = filename
	6 = plain text or command arguments
	7 = parenthesis */
int	set_type(t_tokens *node)
{
	int	flag;
	int	len;

	len = ft_strlen(node->content);
	if (((node->content[0] == '<' || node->content[0] == '>') && len == 1)
		|| (node->content[0] == '>' && len == 2))
		flag = 0;
	else if ((node->content[0] == '<') && len == 2)
		flag = 1;
	else if (node->content[0] == '|' && len == 1)
		flag = 2;
	else if ((node->content[0] == '|' || node->content[0] == '&') && len == 2)
		flag = 3;
	else if (node->content[0] == '(' || node->content[0] == ')')
		flag = 7;
	else if (node->prev && node->prev->type == 1)
		flag = 4;
	else if (node->prev && node->prev->type == 0)
		flag = 5;
	else
		flag = 6;
	return (flag);
}
