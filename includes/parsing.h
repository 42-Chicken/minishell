/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efranco <efranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:26:37 by rguigneb          #+#    #+#             */
/*   Updated: 2025/02/25 11:15:43 by efranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

# include "minishell.h"

typedef enum {
    TOKEN_WORD,       // Mot
    TOKEN_PIPE,       // |
    TOKEN_REDIR_IN,   // <
    TOKEN_REDIR_OUT,  // >
    TOKEN_APPEND,     // >>
    TOKEN_HEREDOC,    // <<
    TOKEN_AND,        // &&
    TOKEN_OR,         // ||
    TOKEN_SEMICOLON,  // ;
    TOKEN_EOF
} TokenType;

typedef struct s_token {
    TokenType type;
    char *value;
    struct s_token *next;
} t_token;
// ---------------------------------
//
// PARSING
//
// ---------------------------------
void		parse_line(t_minishell *data, char *line);
char	*ft_strndup(char *str, int n);

#endif
