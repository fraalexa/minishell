/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:50:18 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 03:03:37 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "minishell.h"

/* Main function */
int		main(int ac, char **av, char **envp);

/* Initialization functions */
void	init_shell(t_shell *shell, char **envp);
void	init_shell_struct(t_shell *shell);
char	**init_env(char **envp);

/* Variable handling */
void	increment_shlvl(char **envp);
char	*get_variable(char *v, char **envp);

/* Prompt */
char	*build_prompt(t_shell *shell);

/* Shell loop */
int		shell_loop(t_shell *shell);
int		interactive_loop(t_shell *shell);

/* Loop helpers */
int		process_shell_line(t_shell *shell);
int		handle_empty_line(t_shell *shell);
int		handle_interactive_line(t_shell *shell);

/* Command processing */
int		process_command_line(t_shell *shell, char *line);
int		process_ast(t_shell *shell, t_ast_node *ast);

/* Utilities */
int		check_quote_error(char *line, char *quote);
void	print_quote_error(char quote);
int		handle_lexer_failure(t_shell *shell, char *line);
void	free_shell(t_shell *shell);

#endif