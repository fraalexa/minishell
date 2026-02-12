/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:50:30 by bepinhei          #+#    #+#             */
/*   Updated: 2026/02/12 02:29:36 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/* Parser main functions */
t_ast_node		*parse(t_token *tokens);
t_ast_node		*parse_pipeline(t_parser *parser);
t_ast_node		*parse_command(t_parser *parser);
void			parser_init(t_parser *parser, t_token *tokens);
void			print_parser_error(t_parser *parser);

/* Parser helpers */
int				match_token(t_parser *parser, t_token_type type);
void			parser_error(t_parser *parser, char *msg);
t_token			*peek_token(t_parser *parser);
t_token			*next_token(t_parser *parser);
int				is_command_end(t_parser *parser);

/* Parser utilities */
t_redir_node	*parse_single_redir(t_parser *parser);
int				handle_redirection(t_parser *parser, t_ast_node *cmd);
int				handle_argument(t_parser *parser, t_ast_node *cmd);
int				process_token(t_parser *parser, t_ast_node *cmd);

/* AST and redirection utilities */
t_ast_node		*create_pipe_node(t_ast_node *left, t_ast_node *right);
t_ast_node		*ast_new_node(t_node_type type);
t_redir_node	*redir_new_node(t_node_type type, char *file);
void			redir_add_back(t_redir_node **redir_list,
					t_redir_node *new_redir);
int				redir_count(t_redir_node *redir);

/* AST helpers */
int				ast_has_pipes(t_ast_node *node);
int				ast_count_pipes(t_ast_node *node);

/* Args utilities */
int				args_count(char **args);
char			**args_add(char **args, char *new_arg);
char			**args_dup(char **args);

/* Memory utilities */
void			free_args(char **args);
void			redir_free(t_redir_node *redir);
void			ast_free(t_ast_node *node);

/* Syntax validation */
int				validate_syntax(t_token *tokens);
int				validate_pipes(t_token *tokens);
int				validate_redirects(t_token *tokens);
int				is_redir_type(t_node_type type);
int				is_redir_token(t_token_type type);
t_node_type		token_to_node_type(t_token_type token_type);

/* Syntax check */

/* Debug utilities */
void			print_indent(int depth);
void			print_node_type(t_node_type type);
void			print_redirects(t_redir_node *redir, int depth);
void			ast_print(t_ast_node *node, int depth);
void			print_node_args(t_ast_node *node, int depth);
void			print_node_children(t_ast_node *node, int depth);

#endif