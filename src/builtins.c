/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:32:02 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/05 11:17:21 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_builtins(t_tokens *token, t_data *data, t_cmd	**cmd, int *i)
{
	if (!ft_strcmp(token->content, "pwd"))
		return (ft_pwd(data, cmd, i));
	else if (!ft_strcmp(token->content, "cd"))
		return (1);
	else if (!ft_strcmp(token->content, "export"))
		return (1);
	else if (!ft_strcmp(token->content, "echo"))
		return (ft_echo(data, cmd, i));
	else if (!ft_strcmp(token->content, "unset"))
		return (1);
	else if (!ft_strcmp(token->content, "env"))
		return (ft_env(data, cmd, i));
	else if (!ft_strcmp(token->content, "exit"))
	{
		ft_putendl_fd("exit", (*cmd)->fd_out);
		ft_exit(data, cmd, i);
		return (1);
	}
	return (0);
}

int	ft_pwd(t_data *data, t_cmd	**cmd, int *i)
{
	char	*temp;

	temp = 0;
	(*i)++;
	temp = getcwd(temp, 0);
	if (!temp)
	{
		set_exit_code(1, true);
		return (0);
	}
	ft_putendl_fd(temp, STDOUT_FILENO);
	free(temp);
	skip_to_pipe(data);
	*cmd = (*cmd)->next;
	set_exit_code(0, true);
	return (1);
}

int	ft_exit(t_data *data, t_cmd **cmd, int *i)
{
	unsigned long long	n;
	int					j;

	n = set_exit_code(0, false);
	j = 0;
	(*i)++;
	skip_to_pipe(data);
	if (!(*cmd)->args[1])
	{
		*cmd = (*cmd)->next;
		exit (set_exit_code(0, false));
	}
	else
	{
		if ((*cmd)->args[2] && !check_exit_arg((*cmd)->args[1]))
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			return (set_exit_code(1, true));
		}
		if (check_exit_arg((*cmd)->args[1]))
			return (set_exit_code(2, true));
		n = ft_atoll((*cmd)->args[1]);
	}
	*cmd = (*cmd)->next;
	exit (set_exit_code(n, true));
}

int	ft_env(t_data *data, t_cmd **cmd, int *i)
{
	t_tokens	*envp;

	envp = data->env;
	(*i)++;
	skip_to_pipe(data);
	*cmd = (*cmd)->next;
	while (envp)
	{
		if (envp->content)
			printf("%s=%s\n", envp->var, envp->content);
		envp = envp->next;
	}
	return (set_exit_code(0, true));
}

int	ft_echo(t_data *data, t_cmd **cmd, int *i)
{
	int	j;
	int	flag;

	j = 0;
	flag = 0;
	(*i)++;
	skip_to_pipe(data);
	if (!(*cmd)->args[1] && printf("\n") && !set_exit_code(0, true))
		return (1);
	while ((*cmd)->args[++j] && !ft_strcmp((*cmd)->args[j], "-n"))
		flag = 1;
	while ((*cmd)->args[j])
	{
		printf("%s", (*cmd)->args[j++]);
		if ((*cmd)->args[j])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	*cmd = (*cmd)->next;
	set_exit_code(0, true);
	return (1);
}
