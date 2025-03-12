/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:28:58 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/12 15:01:02 by rguigneb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "minishell.h"
#include "parsing.h"
#include <limits.h>

t_list	*create_final_lst(t_token *keywords, t_list *args)
{
	t_list	*lst;
	t_list	*current;
	int		index;

	lst = NULL;
	index = ft_lstsize(args);
	while (index > 0)
	{
		current = ft_lstnew(args->content);
		args = args->next;
		if (keywords)
		{
			current->next = ft_lstnew(keywords);
			keywords = keywords->next;
		}
		ft_lstadd_back(&lst, current);
		index--;
	}
	return (lst);
}

void	parse_line(t_minishell *data, char *line)
{
	t_token	*keywords;
	t_token	*args;
	t_token	*half_quoted;
	t_token	*quoted;
	t_list	*new_args;
	t_btree	*tree;
	t_list	*lst;
	char	quote;

	quote = verif_quote(line);
	if (quote == '\'')
		return (data->exit_code = 2, ft_fprintf(STDERR_FILENO,
				ERROR_SINGLE_QUOTE), (void)0);
	else if (quote == '"')
		return (data->exit_code = 2, ft_fprintf(STDERR_FILENO,
				ERROR_DOUBLE_QUOTE), (void)0);
	if (check_priorities(line))
		return (data->exit_code = 2, (void)0);
	half_quoted = NULL;
	args = extract_arg(line, &half_quoted);
	keywords = tokenize(data, line);
	quoted = NULL;
	extract_quote(&quoted, half_quoted);
	init_all_index(keywords, args, quoted);
	new_args = NULL;
	create_lst_args(&new_args, keywords, args, quoted);
	lst = create_final_lst(keywords, new_args);
	lst = create_btree_nodes_lst(lst);
	tree = create_final_tree(lst, 0);
	data->execution_tree = tree;
}
