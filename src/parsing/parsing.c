/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rguigneb <rguigneb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:28:58 by rguigneb          #+#    #+#             */
/*   Updated: 2025/03/13 08:45:33 by rguigneb         ###   ########.fr       */
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

typedef struct s_parsing_lists
{
	t_token	*keywords;
	t_token	*args;
	t_token	*half_quoted;
	t_token	*quoted;
	t_list	*new_args;
	t_list	*lst;
}			t_parsing_lists;

void	parse_line(t_minishell *data, char *line)
{
	t_parsing_lists	p_data;
	t_btree			*tree;
	char			quote;

	ft_bzero(&p_data, sizeof(t_parsing_lists));
	quote = verif_quote(line);
	if (quote == '\'')
		return (data->exit_code = 2, ft_fprintf(STDERR_FILENO,
				ERROR_SINGLE_QUOTE), (void)0);
	else if (quote == '"')
		return (data->exit_code = 2, ft_fprintf(STDERR_FILENO,
				ERROR_DOUBLE_QUOTE), (void)0);
	if (check_priorities(line))
		return (data->exit_code = 2, (void)0);
	p_data.args = extract_arg(line, &p_data.half_quoted);
	p_data.keywords = tokenize(data, line);
	extract_quote(&p_data.quoted, p_data.half_quoted);
	init_all_index(p_data.keywords, p_data.args, p_data.quoted);
	create_lst_args(&p_data.new_args, p_data.keywords, p_data.args,
		p_data.quoted);
	p_data.lst = create_final_lst(p_data.keywords, p_data.new_args);
	p_data.lst = create_btree_nodes_lst(p_data.lst);
	tree = create_final_tree(p_data.lst, 0);
	data->execution_tree = tree;
}
