/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:10:11 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/18 12:01:59 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*temp;
	t_data		data;

	temp = 0;
	(void)argc;
	(void)argv;
	init_data(&data, envp);
	signal_intercepter();
	while (1)
	{
		data.path = get_paths(data.env, data.path);
		temp = readline("minishell$ ");
		if (!temp && printf("exit\n"))
			break ;
		add_history(temp);
		lexer(&data, temp);
		free_list(&data.tokens);
		free(data.pid);
		data.pid = 0;
		unlink("here_doc");
	}
	free_all(0, &data, 0, 1);
	rl_clear_history();
	return (set_exit_code(0, false));
}

void	init_data(t_data *data, char **env)
{
	get_env(env, data);
	data->tokens = 0;
	data->pid = 0;
	data->pipe_fd[0] = 0;
	data->pipe_fd[1] = 0;
	unlink("here_doc");
}

/* This functions breaks the input into tokens according to grammar */
int	lexer(t_data *data, char *str)
{
	int		i;
	int		j;
	char	*token;

	i = 0;
	unlink("here_doc");
	while (str[i] != '\0')
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		if (ft_isforbidden_char(&str[i]))
			return (free_str(str));
		j = token_len(&str[i]);
		if (!j)
			return (free_str(str));
		token = ft_substr(str, i, j);
		i += j;
		if (create_tokens(data, token))
			return (free_str(str));
	}
	free(str);
	parser(data);
	return (0);
}

/* Function to create a node from the token found and cathegorise it */
int	create_tokens(t_data *data, char *str)
{
	t_tokens	*node;

	node = ft_lstnew(str, ft_strdup(""));
	if (!node)
	{
		free_list(&data->tokens);
		return (set_exit_code(1, true));
	}
	ft_lstadd_back(&data->tokens, node);
	node->type = set_type(node);
	if (node->prev && node->prev->type < 2 && node->content[0] == '$')
	{
		check_exit_code(node->content, ": ambiguous redirect", 1);
		return (set_exit_code(1, true));
	}
	return (0);
}
