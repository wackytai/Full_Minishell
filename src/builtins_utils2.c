/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:34:52 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/13 11:39:01 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	free_var(t_tokens **lst)
{
	free((*lst)->content);
	return (1);
}

unsigned char	check_number(char *str)
{
	unsigned long long	n;
	int					s;
	int					i;

	s = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			s = -1;
	n = ft_atoll(&str[i]);
	if (((ft_strlen(str) > 19 && s > 0) || (ft_strlen(str) > 20 && s < 0))
		|| ((n > LLONG_MAX && s > 0) || (n - 1 > LLONG_MAX && s < 0)))
	{
		s = 1;
		n = 2;
		exit_error(str);
	}
	return ((unsigned char)((long long)(n * s)));
}

int	print_error(char *str, char *s1, char *s2)
{
	char	*temp;
	int		i;

	temp = 0;
	i = 0;
	while (s2[i] && s2[i] != '=')
		i++;
	if (s2[i] && s2[i] == '=')
		temp = free_joined(ft_strjoin(s1, ": `"), ft_strdup(&s2[i]));
	else
		temp = free_joined(ft_strjoin(s1, ": `"), ft_strdup(str));
	temp = free_joined(temp, ft_strdup("': not a valid identifier"));
	ft_putendl_fd(temp, STDERR_FILENO);
	free(temp);
	return (1);
}

int	unset_var(t_data *data, t_cmd *cmd)
{
	int	i;
	int	flag;
	int	exit;

	i = 0;
	flag = 0;
	exit = 0;
	while (cmd->args[++i])
	{
		flag = validate_var_name(cmd->args[i], cmd->args[0], cmd->args[i]);
		if (exit)
			flag = 1;
		if (flag)
		{
			exit = 1;
			continue ;
		}
		exit = remove_env_node(&data->env, cmd->args[i]);
	}
	if (flag)
		exit = flag;
	return (exit);
}

int	ft_isbuiltin(char *token)
{
	if (!token)
		return (0);
	if (!ft_strcmp(token, "pwd") || !ft_strcmp(token, "cd")
		|| !ft_strcmp(token, "export") || !ft_strcmp(token, "echo")
		|| !ft_strcmp(token, "unset") || !ft_strcmp(token, "env")
		|| !ft_strcmp(token, "exit"))
		return (1);
	return (0);
}
