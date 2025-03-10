/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/10 08:57:49 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

# include "minishell.h"

typedef enum
{
	TOKEN_WORD,      // Mot
	TOKEN_PIPE,      // |
	TOKEN_REDIR_IN,  // <
	TOKEN_REDIR_OUT, // >
	TOKEN_APPEND,    // >>
	TOKEN_HEREDOC,   // <<
	TOKEN_AND,       // &&
	TOKEN_OR,        // ||
	TOKEN_QUOTED,    // ""
	TOKEN_EOF
}					TokenType;

typedef struct s_token
{
	TokenType		type;
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
// ---------------------------------
//
// PARSING
//
// ---------------------------------
void				parse_line(t_minishell *data, char *line);
char				*ft_strndup(char *str, int n);
int					ft_tokensize(t_token *lst);
unsigned int		get_priority_at(char *str, unsigned int index);

#endif
