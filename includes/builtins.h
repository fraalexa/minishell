/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 00:00:00 by berna             #+#    #+#             */
/*   Updated: 2026/02/12 04:15:46 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		builtin_echo(char **argv, t_shell *msh, t_tkn *tokens);
int		builtin_cd(char **argv, char **envp);
int		builtin_pwd(t_shell *msh, t_tkn *tokens);
int		builtin_export_no_var(char **envp);
int		builtin_export(t_shell *msh, char ***envp, const char *new_var);
int		builtin_unset(char **argv, char ***envp);
int		builtin_env(char **envp, t_shell *msh, t_tkn *token);
int		builtin_exit(char **argv, t_shell *msh, t_tkn *tokens);

/* Helpers */
int		find_env_var(char **envp, const char *var);
void	update_env_var(char **envp, const char *var, const char *value);

/* Export helpers */
int		add_new_variable(char ***envp, t_exp *exp, const char *new_var);
int		handle_addition(t_exp *exp);
int		handle_removal(t_exp *exp);
int		update_variable_entry(char ***envp, t_exp **exp, int i);
int		update_existing_variable(char ***envp, t_exp *exp);
int		find_existing_variable(char ***envp, t_exp **exp);
int		variable_exists(char ***envp, const char *var);
int		update_existing_variable_env(char ***envp, t_exp *exp);
int		parse_variable(const char *new_var, t_exp *exp);
int		add_new_variable_env(char ***envp, t_exp *exp, const char *new_var);
int		sort_envp(char **envp);
int		sanity_check_export(const char *var);
void	handle_w_equal_sign(char *env_var, char *equal_sign);

int		remove_variable(char ***envp, char *var);
int		is_variable_match(const char *env_var, const char *var_name);

int		is_valid_number(const char *str);
int		is_letter(const char *str);
int		is_sign(char *argv);
int		parse_exit_number(const char *str);

#endif
