/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:02:10 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/01 14:05:36 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* This function check for allowed characters following '*' */
int	expand_wildcards(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '*')
		continue ;
	if (i == (int)ft_strlen(str))
		return (0);
	while (str[++i] && str[i] != '>' && str[i] != '<' && !str[i + 1])
		continue ;
	return (i);
}

/* This function reads the directory entries and search for a match wildcard */
int	find_wildcard(DIR *dirp, t_tokens **node)
{
	t_tokens		*wc;
	struct dirent	*preview;

	preview = readdir(dirp);
	wc = 0;
	while (preview)
	{
		if (preview->d_name[0] == '.' && (*node)->content[0] != '.')
		{
			preview = readdir(dirp);
			continue ;
		}
		if (match_wildcard(preview->d_name, (*node)->content))
			if (create_wildcards(&wc, preview->d_name))
				return (1);
		preview = readdir(dirp);
	}
	if (!ft_lstsize(wc))
		return (0);
	update_lst(node, wc);
	return (0);
}

/* This function iterates string received to check match with wildcard */
int	match_wildcard(char *entry, char *ptrn)
{
	int	i;
	int	j;
	int	last_wc;
	int	backtrack;

	i = 0;
	j = 0;
	last_wc = -1;
	backtrack = -1;
	while (ptrn[j] && entry[i])
	{
		if (ptrn[j] == entry[i])
			increment_both(&i, &j);
		else if (ptrn[j] && ptrn[j] == '*')
			update_values(&i, &j, &last_wc, &backtrack);
		else if (last_wc != -1)
			equal_values(&j, &last_wc, &i, pre_increment(&backtrack));
		else
			return (0);
	}
	return (check_asterik(ptrn, &j));
}

/* Function to initialise the wildcard node and list and add that to its end */
int	create_wildcards(t_tokens **wc, char *str)
{
	t_tokens	*node;
	t_tokens	*temp;

	temp = *wc;
	node = ft_lstnew(ft_strdup(str), ft_strdup(""));
	if (!node)
	{
		free_list(wc);
		return (set_exit_code(1, true));
	}
	node->type = 6;
	ft_add_in_order(wc, node);
	return (0);
}
