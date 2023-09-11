/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:32:27 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/11 09:53:48 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

unsigned long long	ft_atoll(char *str)
{
	unsigned long long	res;
	int					i;

	res = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] > 47 && str[i] < 58)
		{
			res = (res * 10) + (str[i] - '0');
			i++;
		}
	}
	return (res);
}

int	check_exit_arg(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (exit_error(str));
	return (0);
}

int	validate_var_name(char *name, char *cmd, char *str)
{
	int	i;
	int	exit;

	i = -1;
	exit = 0;
	if (name[0] != '_' && !ft_isalpha(name[0]))
	{
		print_error(&name[0], cmd, str);
		return (1);
	}
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			exit = 1;
			print_error(&name[i], cmd, str);
			break ;
		}
	}
	return (exit);
}

int	create_export_var(t_cmd *cmd, t_tokens **env)
{
	int			exit;
	int			i;
	int			flag;
	char		**var;
	t_tokens	*temp;

	var = 0;
	i = 0;
	exit = 0;
	flag = 0;
	while (cmd->args[++i])
	{
		var = get_env_var(cmd->args[i]);
		temp = get_env_node(*env, var[0]);
		if (temp && free_var(&temp))
			temp->content = ft_strdup(var[1]);
		else
			flag = export_add_var(env, var, cmd->args[i]);
		if (flag)
			exit = 1;
		free_array(var);
	}
	return (exit);
}

int	export_add_var(t_tokens **env, char **var, char *str)
{
	int			exit;

	exit = 0;
	if (validate_var_name(var[0], "export", str))
		exit = 1;
	else if (!var[1])
		exit = ft_lstadd_back(env, ft_lstnew(0, ft_strdup(var[0])));
	else
		exit = ft_lstadd_back(env, ft_lstnew(ft_strdup(var[1]),
					ft_strdup(var[0])));
	get_rank(env);
	return (exit);
}
