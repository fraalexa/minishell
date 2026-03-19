/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fraalexa <fraalexa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:13:06 by bepinhei          #+#    #+#             */
/*   Updated: 2026/03/19 15:07:35 by fraalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE
# define _DEFAULT_SOURCE

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include "../lib/libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_status
{
	FAILURE,
	SUCCESS
}						t_status;

typedef enum e_token_type
{
	TOKEN_EOF,
	TOKEN_WORD,
	TOKEN_VAR,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}						t_token_type;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APPEND,
	NODE_HEREDOC
}						t_node_type;

typedef enum e_cmd_group
{
	CMD_EXEC,
	CMD_ECHO,
	CMD_CD,
	CMD_PWD,
	CMD_EXPORT,
	CMD_UNSET,
	CMD_ENV,
	CMD_EXIT
}						t_cmd_group;

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	int					quoted;
	struct s_token		*next;
}						t_token;
typedef struct s_redir_node
{
	t_node_type			type;
	char				*file;
	int					quoted;
	struct s_redir_node	*next;
}						t_redir_node;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**args;
	int					*arg_quotes;
	t_redir_node		*redirects;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct s_parser
{
	t_token				*tokens;
	t_token				*current;
	int					error;
	char				*error_msg;
}						t_parser;

typedef struct s_heredoc
{
	int					i;
	int					len;
	int					fd_heredoc;
	char				*fd_heredoc_path;
	char				*eof;
	int					count_hd;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_command
{
	int					ac;
	char				**av;
	char				*cmd;
}						t_command;

typedef struct s_msh
{
	t_command			*cmds;
	char				**envp;
	char				**ex_envp;
	char				**path;
	char				**arg;
	char				*user;
	char				*home;
	char				*hostname;
	char				*pwd;
	char				*prompt;
	char				*line;
	char				*word;
	int					fd_in;
	int					fd_out;
	int					pid;
	int					cmd_count;
	int					pipe_count;
	int					len;
	int					exit_status;
	t_ast_node			*ast_root;
	bool				flag_redir;
	bool				flag_exit;
	bool				non_interactive;
	bool				in_child_exec;
	t_heredoc			*heredoc;
	size_t				word_size;

}						t_shell;

typedef struct s_exp
{
	bool				flag;
	size_t				len;
	size_t				prefix_len;
	char				*no_sign;
	char				*equal_sign;
	char				*add_sign;
	char				*remove_sign;
	char				*var;
	char				*var_name;
	char				*value;
	char				*result;
	char				*new_entry;
	char				*updated_value;
	char				*existing_value;
	char				*to_add;
	char				*to_remove;
	char				*found;
	char				**new_envp;
	int					start;
}						t_exp;

extern volatile int			g_signal;

#endif
