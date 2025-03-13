/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 13:52:20 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

# include "limits.h"
# include "minishell.h"

typedef enum TokenType
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_QUOTED,
	TOKEN_EOF
}					t_e_token_type;

typedef struct s_token
{
	t_e_token_type	type;
	char			*value;
	char			**argv;
	struct s_token	*next;
	int				index;
	int				num;
	unsigned int	priority;
}					t_token;

typedef struct s_direction
{
	t_token			*right_keyword;
	t_token			*left_keyword;
	t_list			*right_arg;
	t_list			*left_arg;
}					t_direction;

typedef struct s_token_data
{
	char			*value;
	int				i;
	int				h;
	unsigned int	priority;
}					t_token_data;
// ---------------------------------
//
// PARSING
//
// ---------------------------------
void				parse_line(t_minishell *data, char *line);
char				*ft_strndup(char *str, int n);
int					ft_tokensize(t_token *lst);
unsigned int		get_priority_at(char *str, unsigned int index);
t_token				*extract_arg(char *line, t_token **head);

void				init_all_index(t_token *tokens, t_token *args,
						t_token *quoted);
t_token				*tokenize(t_minishell *data, char *input);

int					is_keywords(t_token *current);

int					is_keyword(char c, int flag);
int					get_max_lst(t_token *keywords, t_token *args,
						t_token *quoted);
int					line_is_empty(t_token *current);

t_token				*ft_tokenlast(t_token *lst);
void				ft_tokenadd_back(t_token **lst, t_token *new);
t_token				*add_token(t_token **head, t_e_token_type type,
						t_token_data data);

int					without_quote(char *str);

int					verif_quote(char *line);

t_token				*get_index_lst(int index, t_token *keywords, t_token *args,
						t_token *quoted);

int					tab_len(char **str);

char				**add_tab_to_tab(char **old, char **str);
char				**add_to_tab(char **old, char *str);

unsigned int		get_priority_at(char *str, unsigned int index);
bool				check_priorities(char *str);
bool				only_spaces(char *str, unsigned int index);
int					verif_arg(char *str);

void				lst_add_before_last(t_list **lst, t_list *node);
t_list				*get_before_last(t_list *head);

t_btree				*get_last_condition(t_list *lst, unsigned int priority);

bool				remain_node_for_priority(t_list *lst,
						unsigned int priority);
t_list				*left_truncate_lst(t_list *lst, t_btree *stop);
t_list				*right_truncate_lst(t_list *lst, t_btree *stop);

char				*allocate_clean_string(char *value);
void				process_quotes(char *value, char *str, int *i, int *j);
char				*remove_quotes_from_value(char *value);

void				extract_quote(t_token **head, t_token *quoted);
int					check_only_quote(char *str);

int					ft_number_quote(char *str);

int					handle_append(t_minishell *data, t_token **tokens,
						char *input, int *i);

int					handle_and(t_minishell *data, t_token **tokens, char *input,
						int *i);

void				process_token(t_token *current, char ***tab, int *priority);
void				add_new_token(t_list **head, char ***tab, int priority);
void				create_lst_args(t_list **head, t_token *keywords,
						t_token *args, t_token *quoted);

t_btree				*create_final_tree(t_list *remaning_nodes,
						unsigned int priority);

t_list				*create_btree_nodes_lst(t_list *lst);
t_command			*create_command(char **argv, unsigned int priority);

t_btree				*create_redirection_node(t_list **head, t_list *lst,
						bool doubled, t_redirection_types type);

#endif
