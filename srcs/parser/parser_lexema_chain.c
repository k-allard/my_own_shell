/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexema_chain.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwindom <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 04:01:11 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/09 04:01:14 by cwindom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void		delete_list(t_list_lexema **lexema_list, \
				t_list_lexema **prev_node)
{
	t_list_lexema	*lexema_list_tmp;

	lexema_list_tmp = (*lexema_list)->next;
	(*prev_node)->next = NULL;
	free((*lexema_list)->lexema->string);
	free((*lexema_list)->lexema);
	free((*lexema_list));
	*lexema_list = lexema_list_tmp;
}

t_list_lexema	*get_next_lexema_chain(t_list_lexema **lexema_list, \
				t_lexema_type delimeter)
{
	t_lexema		*lexema;
	int				is_not_delimeter_prev;
	t_list_lexema	*chain;
	t_list_lexema	*prev_node;

	prev_node = NULL;
	chain = *lexema_list;
	is_not_delimeter_prev = 1;
	while (*lexema_list && is_not_delimeter_prev)
	{
		lexema = (*lexema_list)->lexema;
		if (lexema->lexema_type != delimeter)
		{
			prev_node = *lexema_list;
			*lexema_list = (*lexema_list)->next;
		}
		else
		{
			delete_list(lexema_list, &prev_node);
			is_not_delimeter_prev = 0;
		}
	}
	return (chain);
}
