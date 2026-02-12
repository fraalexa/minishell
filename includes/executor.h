/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:50:08 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 04:37:39 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/* Executor public prototypes */
int			execute_ast(t_shell *shell, t_ast_node *ast);
int			execute_ast_impl(t_shell *shell, t_ast_node *ast);
char		*check_direct_path(char *cmd);
char		*search_in_env_path(char *cmd, char **envp);
char		*find_path(char *cmd, char **envp);
char		*expand_variable_command(char *cmd_name, char **envp);
void		handle_path_not_found(char *cmd);
void		setup_signals(void);
void		setup_signals_heredoc(void);
void		sigint_handler(int sig);
void		signals_executor(void);

/* Redirections and pipes */
int			apply_redirections(t_shell *shell, t_redir_node *redir,
				int *original_fds);
void		restore_redirections(int *original_fds);
int			execute_builtin(t_shell *shell, char **args, t_cmd_group cmd_type);
t_cmd_group	get_cmd_type(char *cmd);
int			execute_external(t_shell *shell, char **args);
int			execute_pipe_node(t_shell *shell, t_ast_node *node);
#endif
