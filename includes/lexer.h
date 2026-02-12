/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bepinhei <bepinhei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:50:13 by bepinhei          #+#    #+#             */
/*   Updated: 2025/10/25 20:50:45 by bepinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

/* Lexer main functions */
t_token	*lexer(char *input);
int		lexer_loop(t_token **tokens, char *input, int *i, int *quote_state);

/* Token creation and handling */
int		create_word_token(t_token **tokens, char *word, int quote_state);
int		handle_word(t_token **tokens, char *input, int *i, int quote_state);
int		process_quote_open(t_token **tokens, char *input, int *i,
			int *quote_state);

/* Operator handling */
int		handle_operators(t_token **tokens, char *input, int *i);
int		handle_pipe(t_token **tokens, int *i);
int		handle_less(t_token **tokens, char *input, int *i);
int		handle_greater(t_token **tokens, char *input, int *i);

/* Lexer utilities */
int		ft_isoperator(char c);
void	skip_whitespace_z(char *input, int *i);
int		advance_word_pos(char *input, int *i, int quote_state, char quote_char);

/* Word processing */
char	get_quote_char(int quote_state);
int		should_concatenate_token(t_token **tokens, char *input, int start,
			int quote_state);
int		handle_concatenation(t_token **tokens, char *word, int quote_state);
char	*create_word_substr(char *input, int start, int len, int quote_state);
int		merge_adjacent_tokens(t_token *last_token);

/* Token utilities */
t_token	*token_new(t_token_type type, char *value, int quoted);
void	token_del(t_token *token);
void	token_lstclear(t_token **head);
void	token_lstadd_back(t_token **head, t_token *new);
t_token	*token_lstlast(t_token *token);

/* Misc utilities */
int		is_whitespace(char c);

/* Expander functions */
char	*expand_string(char *str, int quoted, t_shell *shell);
int		expand_ast(t_ast_node *ast, t_shell *shell);
int		expand_command_args(t_ast_node *ast, t_shell *shell);
int		expand_redirections(t_redir_node *redir, t_shell *shell);
int		filter_empty_args(char **args);

/* Expander helpers */
char	*expand_quoted_string(char *str, t_shell *shell);
char	*expand_unquoted_string(char *str, t_shell *shell);
char	*process_quoted_chars(char *result, char *inner, t_shell *shell);
char	*append_char_to_result(char *result, char c);

/* Expander utilities */
char	*ft_charjoin(char *s, char c);
char	*get_env_value(char *name, t_shell *shell);
char	*get_var_name(char *str, int *len);
char	*get_expanded_value(char *var_name, int name_len, t_shell *shell);
char	*append_expansion(char *result, char *str, t_shell *shell, int *i);

#endif