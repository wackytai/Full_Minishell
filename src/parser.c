/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:36:32 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/14 12:47:31 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* This fuction isolates the variable name */
char	*separate_var(char *str)
{
	char	*var;
	int		i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == '$' || str[i] == '*' || str[i] == 32 || str[i] == ':'
			|| str[i] == '\'' || str[i] == '\"' || str[i] == '/'
			|| str[i] == '.' || str[i] == ',' || (str[i] == '?' && i == 1)
			|| ft_isdigit(str[i - 1]))
			break ;
	}
	if (i == 1 && str[i - 1] == '$' && str[i] != '?')
		var = ft_strdup("$");
	else if (i == 1 && str[i])
		var = ft_substr(str, 1, i);
	else
		var = ft_substr(str, 1, (i - 1));
	return (var);
}

/* Function to deal with '$' expansion and add it to the content of the token */
char	*ft_expansion(char *str, char c, t_tokens *env)
{
	int		i;
	int		j;
	char	*s;

	j = 0;
	if (!ft_strcmp(str, "$"))
		return (str);
	s = ft_strdup("");
	while (str[j])
	{
		i = j;
		if (c != '\'' && str[i] == '$')
			s = free_joined(s, expand_dollar(str, &i, env));
		else
		{
			while (str[++i] && str[i] != '$')
				continue ;
			s = free_joined(s, ft_substr(str, j, (i - j)));
		}
		j = i;
	}
	free(str);
	return (s);
}

/* Function to search the environment for the variable received
and replace it for its value */
char	*search_var(char *str, t_tokens *env)
{
	while (env)
	{
		if (!ft_strcmp(str, env->var))
			break ;
		env = env->next;
	}
	free(str);
	if (!env)
		return (ft_strdup(""));
	str = ft_strdup(env->content);
	return (str);
}

/* This function remove quotes if found and then checks for '$' expansion */
char	*remove_quotes(char *tk, t_tokens *env)
{
	int		i;
	int		j;
	char	*s;
	char	*temp;

	i = 0;
	j = 0;
	s = ft_strdup("");
	temp = 0;
	while (i < (int)ft_strlen(tk))
	{
		j += skip_quotes(&tk[i]);
		if (tk[i] == '\'' || tk[i] == '\"')
			temp = ft_expansion(ft_substr(tk, i + 1, (j - i - 1)), tk[i], env);
		else
			temp = ft_expansion(ft_substr(tk, i, (j - i + 1)), tk[i], env);
		s = free_joined(s, temp);
		i = ++j;
	}
	free(tk);
	return (s);
}

/* This function selects the tokens enabled to be expanded */
void	parser(t_data *data)
{
	t_tokens	*token;
	t_tokens	*env;

	token = data->tokens;
	env = data->env;
	if (!token || (token && check_token_sequence(token)))
		return ;
	while (token)
	{
		if (token->type < 4 || token->type == 7)
		{
			token = token->next;
			continue ;
		}
		if (token->type > 4 && check_wildcards(&token)
			&& reset_lst(data, token))
			return ;
		reset_lst(data, token);
		if (token->type > 4)
			token->content = remove_quotes(token->content, env);
		token = token->next;
	}
	if (executer(data))
		return ;
}
