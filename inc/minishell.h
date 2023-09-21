/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:05:43 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/09/21 09:18:50 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft_gnl/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd
{
	struct s_cmd	*prev;
	struct s_cmd	*next;
	char			*cmd_path;
	char			**args;
	int				rd_in;
	int				rd_out;
	int				fd_in;
	int				fd_out;
}					t_cmd;

typedef struct s_token
{
	int				rank;
	char			*var;
	char			*content;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_tokens;

typedef struct s_data
{
	t_tokens		*tokens;
	t_tokens		*env;
	char			**path;
	pid_t			*pid;
	int				pipe_fd[2];
}					t_data;

/* lexer.c */
int					main(int argc, char **argv, char **envp);
void				init_data(t_data *data, char **env);
int					lexer(t_data *data, char *str);
int					create_tokens(t_data *data, char *str);

/* lexer_utils.c */
int					ft_isforbidden_char(char *str);
int					ft_isdelimiter(char *str);
int					check_text(char *str);
int					set_type(t_tokens *node);

/* lexer_utils2.c */
int					token_len(char *str);
int					skip_quotes(char *str);

/* parser.c */
char				*separate_var(char *str);
char				*search_var(char *str, t_tokens *env);
char				*ft_expansion(char *str, char c, t_tokens *env);
char				*remove_quotes(char *token, t_tokens *env);
void				parser(t_data *data);

/* parser_utils.c */
int					reset_lst(t_data *data, t_tokens *token);
int					check_token_sequence(t_tokens *token);
int					check_wildcards(t_tokens **t);
char				*expand_dollar(char *str, int *i, t_tokens *env);

/* executer.c */
int					executer(t_data *data);
int					update_cmd_lst(t_tokens *tokens, t_cmd **cmd);
int					exe_tokens(t_data *data, t_cmd **cmd);
int					forking(t_data *data, t_cmd **cmds, int i);
void				skip_to_pipe(t_data *data);

/* executer_utils.c */
int					exe_cmd(t_data *data, t_cmd **cmd);
int					get_cmd_lst(t_tokens *t, t_cmd **cmds);
void				jump_tokens(t_data *data);
int					check_directory(char *str, int flag);
int					check_exit_code(char *s1, char *s2, int flag);

/* executer_utils2.c */
int					check_pipes(t_data *data, t_cmd **cmds);

/* builtins.c */
int					check_builtins(t_data *data, t_cmd	**cmd);
int					update_lsts(t_data *data, int *i);
int					ft_pwd(int out);
int					ft_exit(t_data *data, t_cmd **cmd);
int					ft_env(t_data *data, int out);

/* builtins2.c */
int					ft_echo(t_cmd **cmd, int out);
int					ft_unset(t_data *data, t_cmd **cmd);
int					ft_export(t_data *data, t_cmd **cmd, int out);
int					ft_cd(t_data *data, t_cmd **cmd);
char				*check_path(t_tokens *env, t_cmd *cmd);

/* builtins_utils.c */
unsigned long long	ft_atoll(char *str);
int					check_exit_arg(char *str);
int					validate_var_name(char *name, char *cmd, char *str);
int					create_export_var(t_cmd *cmd, t_tokens **env);
int					export_add_var(t_tokens **env, char **var, char *str);
int					ft_isbuiltin(char *token);

/* builtins_utils2.c */
int					free_var(t_tokens **lst);
unsigned char		check_number(char *str);
int					print_error(char *str, char *s1, char *s2);
int					unset_var(t_data *data, t_cmd *cmd);

/* operators.c */
int					check_operators(t_tokens *token);

/* cmd_utils.c */
char				*is_command(char **paths, char *cmd);
int					check_cmd(char **paths, t_cmd **cmd);
int					cmd_size(t_tokens *tokens);
char				**get_cmd_args(t_tokens *t);

/* files.c */
int					check_files(t_tokens *t, t_cmd *cmd, t_data *data);
int					check_outfile(t_tokens *t, t_cmd *cmd);
int					check_infile(t_tokens *t, t_cmd *cmd, int in, t_data *data);
int					handle_here_doc(t_data *data, t_tokens *t, t_cmd *cmd);
int					here_doc(int fd, t_tokens *t, t_data *data, t_cmd *cmd);

/* process_utils.c */
int					init_pids(t_data *data);
int					update_io(t_data *data, t_cmd *cmds, int pipe_fd[2]);
int					check_fds(t_cmd *cmds, int pipe[2]);
int					handle_pipeline(t_data *data, t_cmd **cmds, int i);
int					wait_processes(t_data *data);

/* wildcards_utils.c */
int					expand_wildcards(char *str);
int					find_wildcard(DIR *dirp, t_tokens **node);
int					match_wildcard(char *entry, char *ptrn);
int					create_wildcards(t_tokens **wc, char *str);

/* wildcards_utils2.c */
void				ft_add_in_order(t_tokens **lst, t_tokens *node);
void				update_lst(t_tokens **node, t_tokens *wc);
int					check_asterik(char *str, int *j);
void				update_values(int *i, int *j, int *last_wc, int *backtrack);
void				equal_values(int *i, int *j, int *k, int *l);

/* wildcards_utils3.c */
int					*pre_increment(int *i);
void				increment_both(int *i, int *j);

/* signals.c */
void				signal_handler(int signal);
void				signal_intercepter(void);
void				child_signal_handler(int signal);
void				child_signal_intercepter(void);
int					set_exit_code(int i, bool flag);

/* env_utils.c */
void				get_env(char **env, t_data *data);
char				**get_paths(t_tokens *env, char **paths);
int					update_env_lst(t_data *data, char **temp);
void				get_rank(t_tokens **lst);
char				**prep_envp(t_tokens *env);

/* env_utils2.c */
char				**get_env_var(char *var);
t_tokens			*get_env_node(t_tokens *env, char *str);
void				update_dirs(t_data *data, char *str);
void				reset_rank(t_tokens **lst);
int					remove_env_node(t_tokens **env, char *name);

/* lst_utils.c */
t_tokens			*ft_lstnew(char *content, char *var_name);
t_tokens			*ft_lstlast(t_tokens *lst);
int					ft_lstsize(t_tokens *lst);
void				ft_lstadd_front(t_tokens **lst, t_tokens *node);
int					ft_lstadd_back(t_tokens **lst, t_tokens *node);

/* lst_utils2.c */
int					count_lst_type(t_tokens *tokens, int type);
t_cmd				*ft_cmdnew(char **cmds);
t_cmd				*cmd_last(t_cmd *lst);
void				cmd_add_back(t_cmd	**lst, t_cmd *node);
t_tokens			*ft_lst_first(t_tokens *lst);

/* print.c */
void				print_exp_var(int flag, int out, t_tokens *node);
void				print_ordered(t_tokens *lst, int out);
void				print_message(int flag, char *str, int i);
void				forbidden_print(int flag, char *str);
int					exit_error(char *str);

/* clean.c */
int					free_all(char *str, t_data *data, t_cmd **cmds, int flag);
int					free_array(char **array);
int					free_list(t_tokens **lst);
char				*free_joined(char *s1, char *s2);
int					free_cmd_lst(t_cmd **lst);

/* clean2.c */
int					free_str(char *str);

#endif