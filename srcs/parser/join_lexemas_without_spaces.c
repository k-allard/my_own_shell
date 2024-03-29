/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_lexemas_without_spaces.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwindom <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 03:35:07 by cwindom           #+#    #+#             */
/*   Updated: 2020/11/09 03:35:10 by cwindom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "parser.h"

void	join_lexemas_without_spaces(t_list_lexema *lexema_chain)
{
	t_list_lexema	*tmp;

	while (lexema_chain)
	{
		tmp = lexema_chain->next;
		if (is_block(lexema_chain->lexema) && tmp &&\
		is_block(tmp->lexema) && tmp->lexema->has_space_before == 0)
		{
			tmp = lexema_chain->next;
			str_join_str(&lexema_chain->lexema->string, tmp->lexema->string);
			lexema_chain->next = tmp->next;
			free(tmp->lexema->string);
			free(tmp->lexema);
			free(tmp);
			tmp = NULL;
		}
		else
			lexema_chain = lexema_chain->next;
	}
}
